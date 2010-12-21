UPDATE `creature_template` SET `ScriptName` = 'boss_freya' WHERE `entry` =32906;
UPDATE `creature_template` SET `unit_flags` = 393220, `ScriptName` = 'creature_eonars_gift' WHERE `entry` =33228;
UPDATE `creature_template` SET `modelid1` = 11686, `modelid2` = 0, `unit_flags` = 33685508, `ScriptName` = 'creature_nature_bomb' WHERE `entry` =34129;
UPDATE `creature_template` SET `unit_class` = 2, `ScriptName` = 'creature_detonating_lasher' WHERE `entry` =32918;
UPDATE `creature_template` SET `ScriptName` = 'creature_ancient_conservator' WHERE `entry` =33203;
UPDATE `creature_template` SET `unit_flags` = 33686022, `ScriptName` = 'creature_healthy_spore' WHERE `entry` =33215;
UPDATE `creature_template` SET `ScriptName` = 'creature_storm_lasher' WHERE `entry` =32919;
UPDATE `creature_template` SET `ScriptName` = 'creature_snaplasher' WHERE `entry` =32916;
UPDATE `creature_template` SET `ScriptName` = 'creature_ancient_water_spirit' WHERE `entry` =33202;


UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` IN (33051, 33691, 33689);
UPDATE creature_template SET faction_A=16, faction_H=16, scriptname='mob_rune_of_power' WHERE entry = 33705;
UPDATE creature_template SET faction_A=16, faction_H=16, scriptname='mob_lightning_elemental', difficulty_entry_1 = 33689 WHERE entry = 32958;
UPDATE `creature_template` SET `unit_flags` = 0, `type_flags` = 0 WHERE `entry` = 33515;
UPDATE `creature_template` SET `equipment_id` = 2500 WHERE `entry` = 33515;


UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `ScriptName` = 'feral_defender_trigger' WHERE `entry` = 34096;
UPDATE `creature_template` SET `ScriptName` = 'mob_feral_defender' WHERE `entry` = 34035;
UPDATE `creature_template` SET `ScriptName` = 'mob_sanctum_sentry' WHERE `entry` = 34014;
UPDATE `creature_template` SET `ScriptName` = 'seeping_trigger' WHERE `entry` = 34098;


UPDATE `creature_template` SET `ScriptName` = 'mob_colossus' WHERE `entry` = 33237;


UPDATE `creature_template` SET `unit_flags` = 32768 WHERE `entry` = 35070;
UPDATE `creature_template` SET `unit_flags` = 32768 WHERE `entry` = 35102;
UPDATE `creature_template` SET `unit_flags` = 32768 WHERE `entry` = 35098;
UPDATE `creature_template` SET `unit_flags` = 32768 WHERE `entry` = 35090;
UPDATE `creature_template` SET `ScriptName` = 'boss_elder_brightleaf' WHERE `entry` =32915;
UPDATE `creature_template` SET `ScriptName` = 'boss_elder_ironbranch' WHERE `entry` =32913;
UPDATE `creature_template` SET `ScriptName` = 'boss_elder_stonebark' WHERE `entry` =32914;
UPDATE `creature_template` SET `ScriptName` = 'creature_sun_beam', `unit_flags` = 33685510, `modelid1` = 11686, `modelid2` = 0 WHERE `entry` =33170;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `unit_flags` = 393220, `ScriptName` = 'creature_iron_roots' WHERE `entry` = 33168;


DELETE FROM `gameobject` WHERE `id`=190586;
INSERT INTO `gameobject` (`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(190586, 599, 1, 1, 880.406, 345.164, 203.706, 0, 0, 0, 0, 1, 180, 0, 1); -- Tribunal Chest Normal
DELETE FROM `gameobject` WHERE `id`=193996;
INSERT INTO `gameobject` (`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(193996, 599, 2, 1, 880.406, 345.164, 203.706, 0, 0, 0, 0, 1, 180, 0, 1);
UPDATE creature_template SET faction_A = 16, faction_H = 16 WHERE entry IN (26632, 31360);
UPDATE `creature_template` SET `modelid1` = 11686, `modelid2` = 0, `unit_flags` = 33686022, `ScriptName` = 'creature_unstable_sun_beam' WHERE `entry` = 33050;


-- The Delicate Sound of Thunder & Lightning Infused Relics
UPDATE quest_template SET ReqCreatureOrGOId1 = 0 , ReqCreatureOrGOCount1 = 0, SpecialFlags = 0, QuestFlags = 138, Method = 0 WHERE entry IN( 11495, 11494);
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299803, `flags_extra` = 257, `ScriptName` = 'boss_general_vezax' WHERE `entry` = 33271;
UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14, `mechanic_immune_mask` = 650854235, `ScriptName` = 'mob_saronite_vapors' WHERE `entry` = 33488;
UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14, `mechanic_immune_mask` = 650854235, `ScriptName` = 'mob_saronite_animus' WHERE `entry` = 33524;


UPDATE `creature_template` SET `unit_flags` = 0, `type_flags` = 0, `ScriptName` = 'boss_hodir' WHERE `entry` = 32845;


UPDATE `creature_template` SET `modelid1` = 11686, `modelid2` = 0 WHERE `entry` IN (34188, 33632, 33802, 34096, 34098);
UPDATE `creature_template` SET `modelid1` = 25865, `modelid2` = 0, `flags_extra` = 0, `ScriptName` = 'mob_flash_freeze' WHERE `entry` = 32938;
UPDATE `creature_template` SET `modelid1` = 28470, `modelid2` = 0, `ScriptName` = 'mob_icicle' WHERE `entry` = 33169;
UPDATE `creature_template` SET `modelid1` = 28470, `modelid2` = 0, `ScriptName` = 'mob_icicle_snowdrift' WHERE `entry` = 33173;
UPDATE `creature_template` SET `modelid1` = 15880, `modelid2` = 0 WHERE `entry` = 33174;
UPDATE `gameobject_template` SET `flags` = 4 WHERE `entry` = 194173;


UPDATE `creature_template` SET `difficulty_entry_1` = 33909, `unit_flags` = 0 WHERE `entry` = 32930;
UPDATE `creature_template` SET `ScriptName` = 'mob_snowpacked_icicle' WHERE `entry` = 33174;


UPDATE `creature_template` SET `faction_A` = 1665, `faction_H` = 1665, `unit_flags` = 32768 WHERE `entry` IN (33325, 32901, 33328, 32901, 32893, 33327, 32897, 33326, 32941, 33333, 33332, 32950, 33331, 32946, 32948, 33330);
UPDATE `creature_template` SET `ScriptName` = 'mob_hodir_priest' WHERE `entry` IN (32897, 33326, 32948, 33330);
UPDATE `creature_template` SET `ScriptName` = 'mob_hodir_shaman' WHERE `entry` IN (33328, 32901, 33332, 32950);
UPDATE `creature_template` SET `ScriptName` = 'mob_hodir_druid' WHERE `entry` IN (33325, 32900, 32941, 33333);
UPDATE `creature_template` SET `ScriptName` = 'mob_hodir_mage' WHERE `entry` IN (32893, 33327, 33331, 32946);
UPDATE `creature_template` SET `modelid1` = 15880, `modelid2` = 0, `ScriptName` = 'toasty_fire' WHERE `entry` = 33342;
UPDATE creature_template SET dmg_multiplier = 15 WHERE entry IN (30451, 30449, 30452);
UPDATE creature_template SET dmg_multiplier = 20 WHERE entry IN (31520, 31535, 31534); 


-- Hodir Flash Freeze
UPDATE `creature_template` SET `difficulty_entry_1` = 33352, `modelid1` = 25865, `modelid2` = 0, `mechanic_immune_mask` = 612597599, `flags_extra` = 0, `ScriptName` = 'npc_flash_freeze_pre' WHERE `entry` = 32926;
UPDATE `creature_template` SET `difficulty_entry_1` = 33353, `mechanic_immune_mask` = 612597599 WHERE `entry` = 32938;
UPDATE `creature_template` SET `modelid1` = 25865, `modelid2` = 0, `faction_A` = 14, `faction_H` = 14, `unit_flags` = 393220, `mechanic_immune_mask` = 612597599, `flags_extra` = 0 WHERE `entry` IN (33352, 33353);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (61969, 61990);
INSERT INTO `spell_linked_spell` VALUES
(61969, 7940, 2, "Hodir Flash Freeze immunity"),
(61990, 7940, 2, "Hodir Flash Freeze immunity");


UPDATE `creature_template` SET `faction_A` = 35, `faction_H` = 35, `unit_flags` = 33554434, `ScriptName` = 'mob_iron_construct', `flags_extra` = 0 WHERE `entry` = 33121;


INSERT INTO `creature_template` VALUES ('33119','0','0','0','0','0','13069','0','0','0','Scorch trigger','','','0','80','80','2','16','16','0','1','1.14286','85','1','0','0','0','0','1','2000','0','1','0','0','0','0','0','0','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','4','1','1','0','0','0','0','0','0','0','94','1','0','0','0','mob_scorch_ground','11159');


UPDATE `creature_template` SET `unit_flags` = 33685510 WHERE `entry` = 33809;
UPDATE `creature_template` SET `flags_extra` = 2 WHERE `entry` = 33661;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `ScriptName` = 'mob_focused_eyebeam' WHERE `entry` IN (33632, 33802);
UPDATE `creature_template` SET `ScriptName` = 'mob_left_arm' WHERE `entry` = 32933;
UPDATE `creature_template` SET `ScriptName` = 'mob_right_arm' WHERE `entry` = 32934;
UPDATE creature_template SET flags_extra = 0 WHERE entry IN (30641, 31521);
UPDATE creature_template SET modelid1 = 29038 WHERE entry IN (30641, 31521);
UPDATE creature_template SET mechanic_immune_mask = 604706780 WHERE entry IN (31506, 31507, 31510, 31508, 31511, 31509, 31512);
UPDATE creature_template SET flags_extra = 2 WHERE entry IN (29326, 30857);
UPDATE `creature_template` SET `dmg_multiplier` = 5 WHERE `entry` = 16011;
UPDATE `creature_template` SET `dmg_multiplier` = 10 WHERE `entry` = 29718;


UPDATE `creature_template` SET `vehicleId` = 336 WHERE `entry` = 33432; -- Leviathan Mk II
DELETE FROM creature WHERE id = 34071;
DELETE FROM vehicle_accessory WHERE entry = 33432;
INSERT INTO vehicle_accessory VALUE (33432, 34071, 7, 1, 'Leviathan Mk II turret');
UPDATE creature_template SET ScriptName = 'boss_mimiron' WHERE entry = 33350;
UPDATE creature_template SET ScriptName = 'boss_leviathan_mk' WHERE entry = 33432;
UPDATE creature_template SET ScriptName = 'boss_leviathan_mk_turret' WHERE entry = 34071;
UPDATE creature_template SET ScriptName = 'mob_proximity_mine' WHERE entry = 34362;
DELETE FROM `creature_model_info` WHERE `modelid`=28831;
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`) VALUES
(28831, 0.5, 7, 2, 0);
UPDATE gameobject_template SET flags = flags &~2 WHERE entry = 175967;


DELETE FROM `creature_model_info` WHERE `modelid`=28831;
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`) VALUES
(28831, 0, 0, 2, 0);
UPDATE `creature_template` SET `flags_extra` = 2 WHERE `entry` IN (33856, 34143, 34050);
UPDATE `creature_template` SET `unit_flags` = 33686018 WHERE `entry` = 34050;
UPDATE `creature` SET `position_x` = 2736.92, `position_y` = 2572.30, `orientation` = 5.723 WHERE `guid` = 137630;
UPDATE `creature_template` SET `ScriptName` = 'boss_vx_001', `unit_flags` = 0, `vehicleid` = 371, `Health_mod` = 375 WHERE `entry` = 33651;
UPDATE `creature_template` SET `ScriptName` = 'boss_aerial_unit', `unit_flags` = 0, `vehicleid` = 388, `Health_mod` = 250 WHERE `entry` = 33670;
UPDATE `creature_template` SET `vehicleid` = 370, `Health_mod` = 156.185 WHERE `entry` = 33432;
UPDATE `creature_template` SET `Health_mod` = 156.185 WHERE `entry` = 34071;


DELETE FROM `creature` WHERE `id`=33651;
INSERT INTO `creature` (`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(33651, 603, 1, 1, 28841, 0, 2744.65, 2569.46, 364.397, 3.14159, 604800, 0, 0, 1742400, 0, 0, 0);
UPDATE `creature_template` SET `unit_flags` = 33686020, `flags_extra` = 2, `ScriptName` = 'rocket_strike' WHERE `entry` = 34047;


UPDATE `creature_template` SET `unit_flags` = 33686020, `type_flags` = 0, `flags_extra` = 2, `ScriptName` = 'magnetic_core' WHERE `entry` = 34068;
UPDATE `gameobject_template` SET `size` = 1.5 WHERE `entry` = 194956;
DELETE FROM `gameobject` WHERE `id`=194956;
INSERT INTO `gameobject` (`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(194956, 603, 1, 1, 2744.65, 2569.46, 364.397, 3.14159, 0, 0, 0.703237, 0.710955, -604800, 0, 1);


UPDATE creature_template SET lootid = 33993, mindmg = 509, maxdmg = 683, attackpower = 805, dmg_multiplier = 35 WHERE entry = 33993;
UPDATE creature_template SET lootid = 33994, mindmg = 509, maxdmg = 683, attackpower = 805, dmg_multiplier = 70 WHERE entry = 33994;
UPDATE creature SET spawnMask = 1 WHERE id = 33993;
UPDATE creature_template SET faction_A = 16, faction_H = 16 WHERE entry = 33994;
UPDATE creature_template SET mindmg = 422, maxdmg = 586, attackpower = 642, dmg_multiplier = 7.5, minrangedmg = 345, maxrangedmg = 509, rangedattackpower = 103 WHERE entry = 33998;
UPDATE `gameobject_template` SET `type` = 1, `flags` = 32, `ScriptName` = 'not_push_button' WHERE `entry` = 194739;
UPDATE `creature_template` SET `unit_flags` = 33554946, `speed_walk` = 0.15, `speed_run` = 0.15, `ScriptName` = 'mob_mimiron_flame' WHERE `entry` = 34363;
UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14, `ScriptName` = 'mob_frost_bomb' WHERE `entry` = 34149;
UPDATE `creature_template` SET `mindmg` = 464, `maxdmg` = 604, `attackpower` = 708, `dmg_multiplier` = 7.5, `minrangedmg` = 353, `maxrangedmg` = 512, `rangedattackpower` = 112, `ScriptName` = 'mob_junk_bot' WHERE `entry` = 33855;
UPDATE `creature_template` SET `mindmg` = 464, `maxdmg` = 604, `attackpower` = 708, `dmg_multiplier` = 15, `minrangedmg` = 353, `maxrangedmg` = 512, `rangedattackpower` = 112, `ScriptName` = 'mob_assault_bot' WHERE `entry` = 34057;
UPDATE `creature_template` SET `mindmg` = 464, `maxdmg` = 604, `attackpower` = 708, `dmg_multiplier` = 10, `minrangedmg` = 353, `maxrangedmg` = 512, `rangedattackpower` = 112, `ScriptName` = 'mob_boom_bot' WHERE `entry` = 33836;
UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14, `ScriptName` = 'mob_emergency_bot' WHERE `entry` = 34147;
UPDATE `creature_template` SET `mindmg` = 464, `maxdmg` = 604, `attackpower` = 708, `dmg_multiplier` = 25, `minrangedmg` = 353, `maxrangedmg` = 512, `rangedattackpower` = 112 WHERE `entry` = 33524;
UPDATE `creature_model_info` SET `bounding_radius` = 0.62, `combat_reach` = 10 WHERE `modelid` = 28992;


-- Mimiron Flames
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `modelid1` = 11686, `ScriptName` = 'mob_mimiron_flame_spread' WHERE `entry` = 34121;


-- Flags sbagliata Deathspeaker 
UPDATE creature_template SET faction_A = 21, faction_H = 21 WHERE entry = 34808;
UPDATE `creature_template` SET `ScriptName` = 'mob_darkrune_watcher' WHERE `entry` = 33453;
UPDATE `creature_template` SET `ScriptName` = 'mob_darkrune_sentinel' WHERE `entry` = 33846;
UPDATE `creature_template` SET `ScriptName` = 'mob_darkrune_guardian' WHERE `entry` = 33388;
UPDATE `creature_template` SET `ScriptName` = 'mob_devouring_flame' WHERE `entry` = 34188;
UPDATE `creature_template` SET `ScriptName` = 'npc_expedition_commander' WHERE `entry` = 33210;
UPDATE `creature_template` SET `ScriptName` = 'mole_machine_trigger' WHERE `entry` = 33282;
UPDATE `creature_template` SET `unit_flags` = 33685506 WHERE `entry` IN (33245,33233);
DELETE FROM `creature` WHERE `id`=33186;


UPDATE `creature_template` SET `speed_walk` = 0.5 WHERE `entry` = 33113;
UPDATE `creature_template` SET `unit_flags` = 0, `type_flags` = 8, `ScriptName` = 'boss_thorim' WHERE `entry` = 32865;


-- Fix quest finale The taste test (Per il recipe Kungaloosh)
UPDATE quest_template SET ReqSpellCast1 = 51962, ReqSpellCast2 = 51962, ReqSpellCast3 = 51962, ReqSpellCast4 = 51962 WHERE entry = 12645;
UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14, `ScriptName` = 'mob_pre_phase' WHERE `entry` IN (32882, 32908, 32885, 33110);
UPDATE `creature_template` SET `unit_flags` = 0, `faction_A` = 14, `faction_H` = 14, `ScriptName` = 'mob_arena_phase' WHERE `entry` IN (32876, 32904, 32878, 32877, 32874, 32875);


UPDATE `creature_template` SET `unit_flags` = 0, `ScriptName` = 'mob_runic_colossus' WHERE `entry` = 32872;
UPDATE `creature_template` SET `unit_flags` = 0, `ScriptName` = 'mob_rune_giant' WHERE `entry` = 32873;
UPDATE `creature_template` SET `modelid1` = 16925, `modelid2` = 0, `ScriptName` = 'thorim_trap_bunny' WHERE `entry` IN (33725, 33282);
UPDATE `creature_template` SET `flags_extra` = 0, `ScriptName` = 'thorim_energy_source' WHERE `entry` = 32892;
UPDATE `creature_template` SET `ScriptName` = 'boss_thorim' WHERE `entry` = 32865;


UPDATE `creature_template` SET `ScriptName` = '' WHERE `entry` = 33725;
UPDATE `creature_template` SET `flags_extra` = 2, `ScriptName` = 'thorim_phase_trigger' WHERE `entry` = 32892;


UPDATE `creature_template` SET `dmgschool` = 4, `dmg_multiplier` = 7.5, `unit_flags` = 33587202, `ScriptName` = 'npc_sif' WHERE `entry` = 33196;


-- Sara
UPDATE `creature_template` SET `unit_flags` = 0, `type_flags` = 0, `mechanic_immune_mask` = 650854235, `ScriptName` = 'boss_sara' WHERE `entry` = 33134;
UPDATE creature_model_info SET bounding_radius = 0.465, combat_reach = 45 WHERE modelid = 29117;
UPDATE `creature` SET `spawndist` = 0 WHERE `id` = 33134;


-- Yogg-Saron
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `unit_flags` = 131076, `mechanic_immune_mask` = 650854235, `ScriptName` = 'boss_yoggsaron' WHERE `entry` = 33288;
UPDATE creature_model_info SET bounding_radius = 0.755, combat_reach = 18 WHERE modelid = 28817;
UPDATE `creature_template` SET  modelid1 = 16946, modelid2 = 0, `minlevel` = 80, `maxlevel` = 80, `faction_A` = 16, `faction_H` = 16, `unit_flags` = 33685510, `speed_walk` = 2, `ScriptName` = 'npc_death_orb' WHERE `entry` = 33882;


-- Brain of Yogg-Saron
UPDATE `creature_template` SET `difficulty_entry_1` = 33954, `faction_A` = 16, `faction_H` = 16, `unit_flags` = 131076, `mechanic_immune_mask` = 650854235, `ScriptName` = 'boss_brain_yoggsaron' WHERE `entry` = 33890;
UPDATE creature_model_info SET bounding_radius = 0.755, combat_reach = 30 WHERE modelid = 28951;


-- Ominous cloud
DELETE FROM `creature` WHERE `id`=33292;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `unit_flags` = 33947654, `type_flags` = 0, `speed_walk` = 0.2, modelid1 = 28549, modelid2 = 0, `ScriptName` = 'npc_ominous_cloud' WHERE `entry` IN (33292, 32406);


-- Guardian of Yogg-Saron
UPDATE `creature_template` SET `minlevel` = 82, `maxlevel` = 82, `faction_A` = 16, `faction_H` = 16, `mindmg` = 123, `maxdmg` = 123, `attackpower` = 123, `dmg_multiplier` = 123, `baseattacktime` = 1800, `mechanic_immune_mask` = 1234, `ScriptName` = 'npc_guardian_yoggsaron' WHERE `entry` = 33136;
UPDATE creature_model_info SET bounding_radius = 0.62, combat_reach = 1.5 WHERE modelid = 28465;


-- Illusions
UPDATE `creature_template` SET modelid1 = 15880, modelid2 = 0, `minlevel` = 82, `maxlevel` = 82, `faction_A` = 16, `faction_H` = 16, `unit_flags` = 33685510, `ScriptName` = 'npc_laughing_skull' WHERE `entry` = 33990;
UPDATE `creature_template` SET `minlevel` = 82, `maxlevel` = 82, `faction_A` = 7, `faction_H` = 7, `mechanic_immune_mask` = 650854235, `ScriptName` = 'npc_illusion' WHERE `entry` IN (33433, 33716, 33717, 33719, 33720, 33567);
UPDATE creature_model_info SET bounding_radius = 0.306, combat_reach = 1.5 WHERE modelid = 28621;
UPDATE creature_model_info SET bounding_radius = 1, combat_reach = 10 WHERE modelid IN (2718, 1687, 2717, 12869);


-- Influence Tentacle
UPDATE `creature_template` SET `minlevel` = 82, `maxlevel` = 82, `faction_A` = 16, `faction_H` = 16, `mindmg` = 123, `maxdmg` = 123, `attackpower` = 123, `dmg_multiplier` = 12 WHERE `entry` = 33943;
UPDATE creature_model_info SET bounding_radius = 0.306, combat_reach = 1.5 WHERE modelid = 28813;


-- Descend into madness portal
UPDATE `creature_template` SET `npcflag` = 16777216, `unit_flags` = 2, `type_flags` = 0, `ScriptName` = 'npc_descend_into_madness' WHERE `entry` = 34072;
DELETE FROM `creature_template` WHERE entry IN (34122, 34123);
INSERT INTO `creature_template` VALUES
('34122','0','0','0','0','0','29074','0','0','0','Descend Into Madness','','Interact','0','81','81','0','35','35','16777216','1','1.14286','1','0','0','0','0','0','1','2000','0','1','2','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','npc_descend_into_madness','11159'),
('34123','0','0','0','0','0','29074','0','0','0','Descend Into Madness','','Interact','0','81','81','0','35','35','16777216','1','1.14286','1','0','0','0','0','0','1','2000','0','1','2','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','1','1','0','0','0','0','0','0','0','0','1','0','0','0','npc_descend_into_madness','11159');


-- Fake npcs
UPDATE `creature_template` SET `unit_flags` = 518, `type_flags` = 0, `flags_extra` = 2, ScriptName = "npc_passive_illusions" WHERE `entry` IN (33436, 33437, 33536, 33535, 33495, 33523, 33441, 33442);


-- Tentacles
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `unit_flags` = 131076, `type_flags` = 0, `ScriptName` = "npc_constrictor_tentacle" WHERE `entry` = 33983;
UPDATE creature_model_info SET bounding_radius = 0.306, combat_reach = 1.5 WHERE modelid = 28815;


UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `unit_flags` = 4, `type_flags` = 0, `mindmg` = 123, `maxdmg` = 123, `attackpower` = 123, `dmg_multiplier` = 123, `baseattacktime` = 1800, `ScriptName` = 'npc_crusher_tentacle' WHERE `entry` = 33966;


UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `unit_flags` = 131076, `ScriptName` = 'npc_corruptor_tentacle' WHERE `entry` = 33985;


UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `mindmg` = 123, `maxdmg` = 132, `attackpower` = 123, `dmg_multiplier` = 12, `type_flags` = 0, `ScriptName` = 'npc_immortal_guardian' WHERE `entry` = 33988;


UPDATE `creature_template` SET `faction_A` = 35, `faction_H` = 35, `npcflag` = 1, `flags_extra` = 2, `ScriptName` = 'keeper_image' WHERE `entry` IN (33213, 33241, 33242, 33244);


UPDATE `creature_template` SET `ScriptName` = 'npc_ys_freya' WHERE `entry` = 33410;
UPDATE `creature_template` SET `ScriptName` = 'npc_ys_hodir' WHERE `entry` = 33411;
UPDATE `creature_template` SET `ScriptName` = 'npc_ys_mimiron' WHERE `entry` = 33412;
UPDATE `creature_template` SET `ScriptName` = 'npc_ys_thorim' WHERE `entry` = 33413;
UPDATE `creature_template` SET `modelid1` = 11686, `modelid2` = 0, `minlevel` = 80, `maxlevel` = 80, `unit_flags` = 33686018, `type_flags` = 0, `ScriptName` = 'npc_sanity_well' WHERE `entry` = 33991;


UPDATE `gameobject_template` SET `flags` = 32, `data2` = 3000, `ScriptName` = 'go_call_tram' WHERE `entry` IN (194914, 194912, 194437);
DELETE FROM gameobject WHERE id = '194437';
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
('194437','603','1','1','2306.87','274.237','424.288','1.52255','0','0','0.689847','0.723956','300','0','1');


UPDATE `creature_template` SET `unit_flags` = 0, `ScriptName` = 'keeper_norgannon' WHERE `entry` = 33686;

