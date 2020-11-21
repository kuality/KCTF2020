DROP TABLE IF EXISTS account;
DROP TABLE IF EXISTS chk_url;

CREATE TABLE account (
	username TEXT not null,
	id TEXT not null,
	password TEXT not null,
	board TEXT not null
);

CREATE TABLE chk_url (
	rid INTEGER AUTOINCREMENT 
	url VARCHAR(255) not null
);