Sample init scripts and service configuration for luascoind
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/luascoind.service:    systemd service unit configuration
    contrib/init/luascoind.openrc:     OpenRC compatible SysV style init script
    contrib/init/luascoind.openrcconf: OpenRC conf.d file
    contrib/init/luascoind.conf:       Upstart service configuration file
    contrib/init/luascoind.init:       CentOS compatible SysV style init script

Service User
---------------------------------

All three Linux startup configurations assume the existence of a "luascoin" user
and group.  They must be created before attempting to use these scripts.
The macOS configuration assumes luascoind will be set up for the current user.

Configuration
---------------------------------

At a bare minimum, luascoind requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, luascoind will shut down promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that luascoind and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If luascoind is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running luascoind without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `share/examples/luascoin.conf`.

Paths
---------------------------------

### Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              `/usr/bin/luascoind`
Configuration file:  `/etc/luascoin/luascoin.conf`
Data directory:      `/var/lib/luascoind`
PID file:            `/var/run/luascoind/luascoind.pid` (OpenRC and Upstart) or `/run/luascoind/luascoind.pid` (systemd)
Lock file:           `/var/lock/subsys/luascoind` (CentOS)

The PID directory (if applicable) and data directory should both be owned by the
luascoin user and group. It is advised for security reasons to make the
configuration file and data directory only readable by the luascoin user and
group. Access to luascoin-cli and other luascoind rpc clients can then be
controlled by group membership.

NOTE: When using the systemd .service file, the creation of the aforementioned
directories and the setting of their permissions is automatically handled by
systemd. Directories are given a permission of 710, giving the luascoin group
access to files under it _if_ the files themselves give permission to the
luascoin group to do so (e.g. when `-sysperms` is specified). This does not allow
for the listing of files under the directory.

NOTE: It is not currently possible to override `datadir` in
`/etc/luascoin/luascoin.conf` with the current systemd, OpenRC, and Upstart init
files out-of-the-box. This is because the command line options specified in the
init files take precedence over the configurations in
`/etc/luascoin/luascoin.conf`. However, some init systems have their own
configuration mechanisms that would allow for overriding the command line
options specified in the init files (e.g. setting `LUASCOIND_DATADIR` for
OpenRC).

### macOS

Binary:              `/usr/local/bin/luascoind`
Configuration file:  `~/Library/Application Support/Luascoin/luascoin.conf`
Data directory:      `~/Library/Application Support/Luascoin`
Lock file:           `~/Library/Application Support/Luascoin/.lock`

Installing Service Configuration
-----------------------------------

### systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start luascoind` and to enable for system startup run
`systemctl enable luascoind`

NOTE: When installing for systemd in Debian/Ubuntu the .service file needs to be copied to the /lib/systemd/system directory instead.

### OpenRC

Rename luascoind.openrc to luascoind and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/luascoind start` and configure it to run on startup with
`rc-update add luascoind`

### Upstart (for Debian/Ubuntu based distributions)

Upstart is the default init system for Debian/Ubuntu versions older than 15.04. If you are using version 15.04 or newer and haven't manually configured upstart you should follow the systemd instructions instead.

Drop luascoind.conf in /etc/init.  Test by running `service luascoind start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

### CentOS

Copy luascoind.init to /etc/init.d/luascoind. Test by running `service luascoind start`.

Using this script, you can adjust the path and flags to the luascoind program by
setting the LUASCOIND and FLAGS environment variables in the file
/etc/sysconfig/luascoind. You can also use the DAEMONOPTS environment variable here.

### macOS

Copy org.luascoin.luascoind.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.luascoin.luascoind.plist`.

This Launch Agent will cause luascoind to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run luascoind as the current user.
You will need to modify org.luascoin.luascoind.plist if you intend to use it as a
Launch Daemon with a dedicated luascoin user.

Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
