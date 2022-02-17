-- 1 up
CREATE TABLE users (
    id serial PRIMARY KEY,
    nick text NOT NULL UNIQUE,
    data jsonb
);
-- 1 down
DROP TABLE users;

-- 2 up
CREATE TABLE messages (
    id serial PRIMARY KEY,
    created_at timestamp with time zone DEFAULT now(),
    user_id integer NOT NULL REFERENCES users(id),
    msg text NOT NULL
);
-- 2 down
DROP TABLE message;

-- 3 up
CREATE OR REPLACE FUNCTION messages_notify()
  RETURNS trigger AS $$
BEGIN
  PERFORM pg_notify('new_message',
                    json_build_object('id', NEW.id,
                                      'msg', NEW.msg,
                                      'nick', nick,
                                      'created_at', NEW.created_at)::text)
  FROM users
  WHERE id = NEW.user_id;

  RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER messages_notify
  AFTER INSERT ON messages
  FOR EACH ROW
  EXECUTE PROCEDURE messages_notify();
-- 3 down
DROP FUNCTION messages_notify();
