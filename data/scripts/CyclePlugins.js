var plugins = plugin.list();
var currentPlugin = -1;

var nextPlugin = function()
{
    currentPlugin = (currentPlugin + 1) % plugins.length;
    viewer.loadPainter(plugins[currentPlugin]);
};

nextPlugin();
timer.start(5000, nextPlugin);
