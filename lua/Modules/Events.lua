-- Provides access to MacroQuest2 functions and commands
mq = require('mq');
ImGui = require('ImGui');

Debug("Events Script");

--Zenith/Genbot Self Commands Usage: /gb or /z7
--[MQ2] Genbot #1#
--[MQ2] Zenith #1#
function Event_SelfEcho(line, SelfEchoText)
	print("Event_SelfEcho");
    print(line);
    print(SelfEchoText);
	mq.flushevents(Event_SelfEcho);
end

--[MQ2] Genbot #1#
mq.event("SelfEcho0", "[MQ2] Genbot #1#", Event_SelfEcho);
--[MQ2] Zenith #1#
mq.event("SelfEcho1", "[MQ2] Zenith #1#", Event_SelfEcho);


--Listen to Chat Channels [Tell, Say].
--You told Person, 'Something'
--Person tells you, 'Something'
--You say, 'Something'
--Person says, 'Something'
function Event_AltTell(line, ChatSender, ChatText)
	if string.match(line, 'told') or string.match(line, 'tells') then
		ChatType = 'Tell';
	elseif string.match(line, 'says') then
		ChatType = 'Say';
	end	
	if ChatSender == 'You' then ChatSender = mq.TLO.Me.CleanName(); end
	
	print("Event_AltTell");
    print(line);
    print(ChatSender);
    print(ChatText);
    print(ChatType);
	mq.flushevents(Event_AltTell);
end

--Tell
mq.event("AltTell0", "#*#you told #1#, '#2#'", Event_AltTell);
mq.event("AltTell1", "#*##1# tells you, '#2#'", Event_AltTell);
--Say
mq.event("AltTell2", "#*##1# say, '#2#'", Event_AltTell);
mq.event("AltTell3", "#*##1# says, '#2#'", Event_AltTell);


--Listen to Chat Channels [EQBC].
function Event_EQBCSAY(line, ChatSender, ChatText, ChatType)
	print("Event_EQBCSAY");
    print(line);
    print(ChatSender);
    print(ChatText);
    if ChatType == 'msg' then 
	ChatType = 'EQBC';
	else 
	ChatType = 'EQBC';
	end
	print(ChatType);
	mq.flushevents(Event_EQBCSAY);
end

--EQBC Say
mq.event("EQBCSAY0", "<#1#> #2#", Event_EQBCSAY);
--EQBC Tell
mq.event("EQBCSAY1", "[#1#(#3#)] #2#", Event_EQBCSAY);


--Listen to Chat Channels [Group, Guild, Raid].
--You tell your party, 'Something'
--You say to your guild, 'Something'
--You tell your raid, 'Something'
--Person tells the group, 'Something'
--Person tells the guild, 'Something'
--Person tells the raid, 'Something'
function Event_GGRSay(line, ChatSender, ChatText, ChatType)
if ChatSender == 'You' then ChatSender = mq.TLO.Me.CleanName(); end
if ChatType == 'party' then ChatType = 'group'; end
	print("Event_GGRSay");
    print(line);
    print(ChatSender);
    print(ChatText);
    print(ChatType);
	mq.flushevents(Event_GGRSay);
end

--Group, Raid Self
mq.event("GGRSay0", "#*##1# tell your #3#, '#2#'", Event_GGRSay);
--Guild Self
mq.event("GGRSay1", "#*##1# say to your #3#, '#2#'", Event_GGRSay);
--Group, Guild, Raid Others
mq.event("GGRSay4", "#*##1# tells the #3#, #*#'#2#'", Event_GGRSay);


--Listen to Chat Channels [OOC].
--You say out of character, 'Something'
--Person says out of character, 'Something'
function Event_OOCSay(line, ChatSender, ChatText, ChatType)
if ChatSender == 'You' then ChatSender = mq.TLO.Me.CleanName(); end
if ChatType == 'character' then ChatType = 'OOC'; end
	print("Event_OOCSay");
    print(line);
    print(ChatSender);
    print(ChatText);
    print(ChatType);
	mq.flushevents(Event_OOCSay);
end

--OOC
mq.event("OOCSay0", "#*##1# say#*# out of #3#, '#2#'", Event_OOCSay);


--Listen to Chat Channels [Shout].
--You shout, 'Something'
--Person shouts, 'Something'
function Event_ShoutSay(line, ChatSender, ChatText, ChatType)
	if ChatSender == 'You' then ChatSender = mq.TLO.Me.CleanName(); end
	ChatType = 'Shout';
	print("Event_ShoutSay");
    print(line);
    print(ChatSender);
    print(ChatText);
    print(ChatType);
	mq.flushevents(Event_ShoutSay);
end

--Shout
mq.event("ShoutSay0", "#*##1# shout#*#, '#2#'", Event_ShoutSay);


--Listen to Chat Channels [Channels].
--You tell Channel:#, 'Something'
--Person tells Channel:#, 'Something'
function Event_ChannelSay(line, ChatSender, ChatText, ChatType, ChatNumber)
	if ChatSender == 'You' then ChatSender = mq.TLO.Me.CleanName(); end
	print("Event_ChannelSay");
    print(line);
    print(ChatSender);
    print(ChatText);
    print(ChatType);
    print(ChatNumber);
	mq.flushevents(Event_ChannelSay);
end

--Channels
mq.event("ChannelSay0", "#*##1# tell#*# #3#:#4#, '#2#'", Event_ChannelSay);
