public class Elevador{
    int atual=0;
    int totalAndares;
    int capacidade;
    int presentes=0;

    Elevador(int capacidade, int totalandares){
        this.capacidade =capacidade;
        this.totalAndares=totalandares;
    }

    void entrar(){
        if(this.presentes<this.capacidade){
            this.presentes++;
            System.out.println("mais uma pessoa, pessoas presentes: " + this.presentes);
        }else
        System.out.println("o elevador esta cheio");
    }

    void sair(){
        if(this.presentes>0){
            this.presentes--;
            System.out.println("saiu uma pessoa, pessoas presentes:" + this.presentes);        
        }else
    System.out.println("tem ninguem");
    } 

    void subir(){
        if(this.atual<this.totalAndares){
        this.atual ++;
        System.out.println("subindo, andar atual:" + this.atual);
        }else
        System.out.println("ja ta no topo");
    }

    void descer(){
        if(this.atual>0){
            this.atual--;
            System.out.println("descendo, andar atual:" + this.atual);
        }else
        System.out.println("tadescido");
    }


}

