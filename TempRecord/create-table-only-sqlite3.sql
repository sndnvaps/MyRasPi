PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;

CREATE TABLE temps(
   name DEFAULT 'DHT22.Temperature',
   tdatetime DATETIME DEFAULT (datetime('now','localtime')),
   temperature NUMERIC NOT NULL,
   humidity NUMERIC NOT NULL
);

COMMIT;

