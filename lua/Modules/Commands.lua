-- Provides access to MacroQuest2 functions and commands
mq = require('mq');
ImGui = require('ImGui');

Debug("Commands Script");

-- Bind the /genbot command
mq.bind('/gb', function(args)
    local command = '/echo [MQ2] Genbot ' .. args
    mq.cmd(command);
end);

-- Bind the /zenith command
mq.bind('/z7', function(args)
    local command = '/echo [MQ2] Zenith ' .. args
    mq.cmd(command);
end);

-- Bind the /zenith command
--mq.bind('/tss', readIniKeys);
