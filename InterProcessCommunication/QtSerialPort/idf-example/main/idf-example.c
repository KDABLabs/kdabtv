#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"

// uart constants
#define UART_PORT_NUM   0
#define UART_RXD        5
#define UART_TXD        4
#define BUF_SIZE        1024

#define TASK_STACK_SIZE 3072

static float VOLTAGE     = 0.0;
static float SPEED       = 0.0;
static float MAX_VOLTAGE = 5.0;
static float STEP        = 0.5;
static float TIME        = 0.0;

void updateSpeed()
{
  if (SPEED != VOLTAGE) {
    TIME += 0.001; // dt is portTICK_PERIOD_MS * 0.001
    SPEED += ((VOLTAGE - SPEED) * TIME);
    if (SPEED == VOLTAGE)
      TIME = 0.0;
  }
}

void command_loop_task(void *args)
{
  uart_config_t uart_config = {
    .baud_rate  = 115200,
    .data_bits  = UART_DATA_8_BITS,
    .parity     = UART_PARITY_DISABLE,
    .stop_bits  = UART_STOP_BITS_1,
    .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_DEFAULT,
  };

  // setup uart
  ESP_ERROR_CHECK(uart_driver_install(UART_PORT_NUM,
                                      BUF_SIZE * 2,
                                      0,
                                      0,
                                      NULL,
                                      0));
  ESP_ERROR_CHECK(uart_param_config(UART_PORT_NUM, &uart_config));
  ESP_ERROR_CHECK(uart_set_pin(UART_PORT_NUM,
                               UART_TXD,
                               UART_RXD,
                               UART_PIN_NO_CHANGE,
                               UART_PIN_NO_CHANGE));

  const char *TAG_COMMAND = "COMMAND";
  const char *TAG_SPEED   = "SPEED";
  const char *TAG_VOLTAGE = "VOLTAGE";

  // buffer to read into
  uint8_t *data = (uint8_t *)malloc(BUF_SIZE);

  while (1) {
    // read
    int len = uart_read_bytes(UART_PORT_NUM, data, (BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);

    updateSpeed();
    ESP_LOGI(TAG_SPEED, "%f", SPEED);
    ESP_LOGI(TAG_VOLTAGE, "%.1f", VOLTAGE);

    // just echo back
    uart_write_bytes(UART_PORT_NUM, (const char *)data, len);

    // handle the command
    if (len) {
      // data[len] = '\0';
      for (int i = 0; i < len; ++i) {
        if (*((const char *)data + i) == '+') {
          ESP_LOGI(TAG_COMMAND, "+ | -> -> incr motor speed");
          if (VOLTAGE < MAX_VOLTAGE)
            VOLTAGE += STEP;
        }
        else if (*((const char *)data + i) == '-') {
          ESP_LOGI(TAG_COMMAND, "- | <- <- decr motor speed");
          if (VOLTAGE > 0.0)
            VOLTAGE -= STEP;
        }
        else
          ESP_LOGI(TAG_COMMAND, "%s | ?? ?? INVALID COMMAND!", *((const char *)data + i));
      }
    }
  }
}

void app_main(void)
{
  xTaskCreate(command_loop_task, "uart_command_loop_task", TASK_STACK_SIZE, NULL, 10, NULL);
}
