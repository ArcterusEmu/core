-- Import this SQL into character database.
DROP TABLE IF EXISTS `gmisland_teleport`;
CREATE TABLE `gmisland_teleport` (
`map` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
`x` DOUBLE NOT NULL DEFAULT '0',
`y` DOUBLE NOT NULL DEFAULT '0',
`z` DOUBLE NOT NULL DEFAULT '0',
`orientation` DOUBLE NOT NULL DEFAULT '0',
`comment` VARCHAR(255),
PRIMARY KEY (`map`)
) ENGINE = MYISAM DEFAULT CHARSET=utf8;

INSERT INTO `gmisland_teleport` (
`map`,`x`,`y`,`z`,`orientation`,`comment`)
VALUES (
'13','1.118799','0.477914','-144.708650','3.133046','Jail Box');




-- Import this SQL into character database.
DROP TABLE IF EXISTS `unused_area_teleport`;
CREATE TABLE `unused_area_teleport` (
`map` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0',
`x` DOUBLE NOT NULL DEFAULT '0',
`y` DOUBLE NOT NULL DEFAULT '0',
`z` DOUBLE NOT NULL DEFAULT '0',
`orientation` DOUBLE NOT NULL DEFAULT '0',
`comment` VARCHAR(255),
PRIMARY KEY (`map`)
) ENGINE = MYISAM DEFAULT CHARSET=utf8;

INSERT INTO `unused_area_teleport` (
`map`,`x`,`y`,`z`,`orientation`,`comment`)
VALUES (
'13','1.118799','0.477914','-144.708650','3.133046','Jail Box');