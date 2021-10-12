
workspace {
 
    model {
        user = person "User"
         
         softwareSystem = softwareSystem "Allegro" {
         
         konto = container "system zarzadzania kontami"{
          this -> user " przeslanie maila z linkiem resetujacym"
         user -> this "przekazanie nowego hasla"
          user -> this "reset hasla przez e-mail" "2fa"
       
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