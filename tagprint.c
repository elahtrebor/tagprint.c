#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define _ ); 
#define print printf(
#define and &&
#define or || 
#define ne !=
#define eq ==

#define MAX_SIZE 4096

enum STATES { BEGIN_TAG, END_TAG };

typedef struct t_parser{
   char *string;
   int tag_state;
   int len;
   int cnt;
} parser;

char *colors[][2] = {
 {"black",  "\e[0;30m"},
 {"red",    "\e[0;31m"}, 
 {"green",  "\e[0;32m"},
 {"orange", "\e[0;33m"},
 {"yellow", "\e[0;93m"},
 {"blue",   "\e[0;34m"},
 {"magenta","\e[0;35m"},
 {"cyan",   "\e[0;36m"},
 {"white",  "\e[0;37m"},
 {"reset",  "\e[0m"}
};

 void setColor(char *color){
             int i;
             for ( i =0; i<=8; i++){
              if(strcmp(colors[i][0], color) == 0){
               printf("%s", colors[i][1]); 
                }
            }
}

//INTERPRET THE TAG AND COMMAND
void translate(parser *p, char *tag){
    // TURN OFF COLOR IF MATCH END TAG ELSE SET COLOR
   if(tag[0] eq '/') { 
    setColor("reset");  
    }else if(strcmp(tag, "br") eq 0){
       print "\n" _
    } 
    else {
    setColor(tag);          
    }      
 }

// PARSE THE TAG              
parser *parseTag(parser *p){
 char pbuff[MAX_SIZE];
  int x = 0;   
 while(p->string[p->cnt] ne '\0' and p->string[p->cnt] ne '>'){
  if(p->string[p->cnt] ne '<'){
     pbuff[x++] = p->string[p->cnt++]; 
     }
   else { p->cnt++; }
  }
  pbuff[x++] = '\0';
  translate(p, pbuff);
  memset(pbuff, 0, MAX_SIZE);
 return p;
}

parser *parse(parser *p){
 // iterate through the string
 for(p->cnt = 0;p->cnt<=p->len;p->cnt++){
   switch( p->string[p->cnt] ){
     case '<':
       p->tag_state = BEGIN_TAG; 
       parseTag(p); 
       break;    
     case '/':
       if(p->tag_state eq BEGIN_TAG){
          p->tag_state = END_TAG;
          parseTag(p); 
         } 
       else { 
          print "%c", p->string[p->cnt] _ 
        }
       break;    
     default:  
       print "%c", p->string[p->cnt] _
       break;
     }
  }  
return p;
}

parser *parser_new(parser *this, char *s){
 this->string = strdup(s);
 this->len = strlen(this->string);
 this->cnt = 0;
 return this;
}
   
void help(void){
 print "TAG PRINTER.\n" _
 print "Example: tagprint \"This is <green>green</green>\"\n\n" _
 exit(0);
}

int main(int argc, char* argv[]){
 if(argc < 2){ help(); }
 parser *p = malloc(sizeof(parser));
 p = parser_new(p, argv[1]); 
 p = parse(p);
 free(p->string);
 free(p);
return 0;

}
