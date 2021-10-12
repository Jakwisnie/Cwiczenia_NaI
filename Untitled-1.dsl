workspace {
 
    model {
        user = person "User"
        redis = softwareSystem "Redis"
        softwareSystem = softwareSystem "Game" {
            webapp = container "Single Page Application" "SPA for site and game" {
                user -> this "Uses"
            }
 
            webAppServer = container "Web application server" "Servers static web application" {
                this -> webapp "Serves"
            }
 
            api = container "API" "Users and game management" {
                webApp -> this "Makes requests" "Rest API"
 
                accounts = component "Accounts" "Management of user access to site" {
                    webapp -> this "Authorizes by" "JWT"
                    webapp -> this "Manages account by" "Rest API"
                }
 
                characters = component "Characters" "Managament of character in specific game" {
                    this -> accounts "Authorizes current user by" "JWT"     
                    webapp -> this "Manages specific character by" "Rest API"
                }
 
                servers = component "Servers" "Infmation about selected game server" {
                    this -> accounts "Authorizes current user by" "JWT"
                    webapp -> this "Reads information about servers and list of all characters" "Rest API"
                }
 
                userInfo = component "User info" "Management character information in specific game, like: backpack, location" {
                    webapp -> this "Manages character information by" "Websocket"
                    this -> accounts "Authorizes current user by" "JWT"
                    this -> this "Sends information about update" "via Redis Pub/Sub"
                }
 
                actions = component "Actions" "Management of user actions like: Go to location" {
                    this -> accounts "Authorizes current user by" "JWT""
                    this -> userInfo "Sends information about character update" "Redis Pub/Sub"
                    webapp -> this "Creates, Reads about actions by" "Websocket"
                }
            }
 
            container "Users Database" "All informations about users. Additionally, has information if character is created in specific game." {
                api -> this "Reads from and writes to"
                accounts -> this "Reads hashed passwords from"
                servers -> this "Reads information about created characters"
            }
 
            container "Game Database" "All informations about selected game: characters, items..." {
                api -> this "Reads fronm and writes to"
                characters -> this "Reads, updates or creates information about user character"
                userInfo -> this "Writes and reads from"
                actions -> this "Writes and reads from"
            }
 
            container "Redis" {
                api -> this "Informs/Watching about update" "via pub/sub"
            }
        }
    }
 
    views {
        systemContext softwareSystem {
            include *
            autolayout lr
        }
 
        container softwareSystem {
            include *
            autolayout lr
        }
 
        component api {
            include *
            autolayout lr
        }
 
        theme default
    }
 
}