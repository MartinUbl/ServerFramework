-- Main database structure file

-- server_info table
DROP TABLE IF EXISTS server_info;
CREATE TABLE server_info (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Identifier',
  `server_name` varchar(32) NOT NULL DEFAULT 'NULL',
  `ip` varchar(32) NOT NULL DEFAULT '127.0.0.1',
  `locked` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_server_name` (`server_name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Server Info';

-- initial data for server_info
INSERT INTO server_info VALUES (1,'Testing Framework Server','127.0.0.1',0);
