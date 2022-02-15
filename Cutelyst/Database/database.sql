-- 1 up
CREATE TABLE big_table (
   id integer
);
-- 1 down
DROP TABLE big_table;

-- 2 up
INSERT INTO big_table (id) (SELECT generate_series(1, 100000));
-- 2 down
TRUNCATE big_table;
