workspace {
 
    model {
        user = person "User"
        
         softwareSystem = softwareSystem "Allegro" {
         konto = container "system zarzadania kontami"{
          user -> this "logowanie e-mail" "2fa"
         }
         
         
         
        }
        faceboook = softwareSystem "Facebook" {
          facebook = container "facebook" {
                user -> this "logowanie facebook""OAuth 2.0"
                this -> konto "zalogowanie"
        }
        }
        gooogle = softwareSystem "Google" {
        
         google = container "google" {
                user -> this "logowanie google""OAuth 2.0"
                this -> konto "zalogowanie"
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
  systemlandscape softwareSystem {
               include *
            autolayout lr
        }
       
 
        theme default
    }
 
}