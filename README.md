![oidc-agent logo](https://raw.githubusercontent.com/indigo-dc/oidc-agent/master/logo_wide.png)
<!-- [![Build Status](https://jenkins.indigo-datacloud.eu/buildStatus/icon?job=Pipeline-as-code/oidc-agent/master)](https://jenkins.indigo-datacloud.eu/job/Pipeline-as-code/job/oidc-agent/job/master/) -->
[![License](https://img.shields.io/github/license/indigo-dc/oidc-agent.svg)](https://github.com/indigo-dc/oidc-agent/blob/master/LICENSE)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/indigo-dc/oidc-agent.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/indigo-dc/oidc-agent/alerts/)
[![Language grade](https://img.shields.io/lgtm/grade/cpp/g/indigo-dc/oidc-agent.svg?logo=lgtm&logoWidth=18&label=code%20quality)](https://lgtm.com/projects/g/indigo-dc/oidc-agent/context:cpp)
[![Code size](https://img.shields.io/github/languages/code-size/indigo-dc/oidc-agent.svg)](https://github.com/indigo-dc/oidc-agent/tree/master/src)
[![Release date](https://img.shields.io/github/release-date/indigo-dc/oidc-agent.svg)](https://github.com/indigo-dc/oidc-agent/releases/latest)
[![Release version](https://img.shields.io/github/release/indigo-dc/oidc-agent.svg)](https://github.com/indigo-dc/oidc-agent/releases/latest)
<!-- [![Commits since latest release](https://img.shields.io/github/commits-since/indigo-dc/oidc-agent/latest.svg)](https://github.com/indigo-dc/oidc-agent/compare/latest...master) -->
<!-- [![Commit activity](https://img.shields.io/github/commit-activity/m/indigo-dc/oidc-agent.svg)](https://github.com/indigo-dc/oidc-agent/graphs/commit-activity) -->
<!-- [![Github downloads](https://img.shields.io/github/downloads/indigo-dc/oidc-agent/total.svg?label=github%20downloads&logo=github&style=flat)](https://github.com/indigo-dc/oidc-agent/releases) -->

# oidc-agent
oidc-agent is a set of tools to manage OpenID Connect tokens and make them easily usable
from the command line. We followed the
[`ssh-agent`](https://www.openssh.com/) design, so users can
handle OIDC tokens in a similar way as they do with ssh keys.

`oidc-agent` is usually started in the beginning of an X-session or a login session.
Through use of environment variables the agent can be located and used to handle
OIDC tokens.

The agent initially does not have any account configurations loaded.  You can load an
account configuration by using `oidc-add`.  Multiple account configurations may
be loaded in `oidc-agent` concurrently.  `oidc-add` is also used to remove a loaded
configuration from `oidc-agent`. `oidc-gen` is used to initially generate an account
configurations file [(Help for different
providers)](https://indigo-dc.gitbooks.io/oidc-agent/provider.html).

**Full documentation** can be found at https://indigo-dc.gitbooks.io/oidc-agent/.

We have a low-traffic **mailing list** with updates such as critical security incidents and new releases: [Subscribe oidc-agent-user](https://www.lists.kit.edu/sympa/subscribe/oidc-agent-user)


## Installation
Current releases are available at [GitHub](https://github.com/indigo-dc/oidc-agent/releases) or http://repo.data.kit.edu/

### Debian Packages
- `sudo apt-key adv --keyserver hkp://pgp.surfnet.nl --recv-keys ACDFB08FDC962044D87FF00B512839863D487A87`

- Depending on your distribution, choose one of the following lines:
     ```
     sudo add-apt-repository "deb http://repo.data.kit.edu/debian/buster ./"
     sudo add-apt-repository "deb http://repo.data.kit.edu/debian/stretch ./"
     sudo add-apt-repository "deb http://repo.data.kit.edu/debian/bullseye ./"
     sudo add-apt-repository "deb http://repo.data.kit.edu/ubuntu/bionic ./"
     sudo add-apt-repository "deb http://repo.data.kit.edu/ubuntu/xenial ./"
     ```
- `sudo apt-get update`
- `sudo apt-get install oidc-agent`

### MacOS
```
brew tap zachmann/x11-ssh-askpass
brew tap indigo-dc/oidc-agent
brew install x11-ssh-askpass
brew install oidc-agent
```

### From Source
Refer to the [documentation](https://indigo-dc.gitbooks.io/oidc-agent/install.html#from-source)
