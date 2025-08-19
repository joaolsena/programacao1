
public class principal{
    public static void main(String[] args){
Elevador el= new Elevador(3, 3);
for(int a=0; a<4; a++)
el.entrar();
for(int a=0; a<4; a++)
el.sair();
for(int a=0; a<4; a++)
el.subir();
for(int a=0; a<4; a++)
el.descer();
    }
}