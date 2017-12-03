#include <vector>
#include <tr1/unordered_map>
#include "gurobi_c++.h"


using namespace std;

int main(int argc, char *argv[]) {
    try {
        GRBEnv env = GRBEnv();
        GRBModel model = GRBModel(env);
        
        int nodes, arcs, source, target, k;
        cin >> nodes >> arcs >> source >> target >> k;
        
        vector< std::tr1::unordered_map<int, GRBVar> > graph(nodes);
        
        char varname[10];
        for(int i = 0; i < arcs; i++) {
            int arcOrig, arcDest, arcCost;
            cin >> arcOrig >> arcDest >> arcCost;
            
            // X_[%d,%d] é o nome da variável do arco
            sprintf(varname, "X_[%d,%d]", arcOrig, arcDest);
            
            graph[arcOrig][arcDest] = model.addVar(0.0, 1.0, arcCost, GRB_BINARY, varname);
        }
        
        // função objetiva
        model.set(GRB_IntAttr_ModelSense, GRB_MINIMIZE);
        
        // restrição source
        // percorre todos os adjacentes de source. a soma de todas essas arestas deve ser igual a k+1.
        GRBLinExpr r1 = GRBLinExpr();
        for(auto j: graph[source]) {
            r1 += j.second;
        }
        model.addConstr(r1 == k + 1, "R1");
        
        // restricao target
        // procura todas arestas que entram em target. a soma de todas essas arestas deve ser igual a k+1.
        GRBLinExpr r2 = GRBLinExpr();
        for(int v = 0; v < graph.size(); v++) {
            if(graph[v].find(target) != graph[v].end()) {
                r2 += graph[v][target];
            }
        }
        model.addConstr(r2 == k + 1 , "R2");
        
        // restrição caminhos disjuntos nos vértices
        // para cada vertice v (diferente de source e target), procura todas as arestas que entram em v. a soma de todas essas arestas deve ser menor ou igual a 1.
        for(int v = 0; v < graph.size(); v++) {
            if (v == source || v == target)
                continue;
            
            GRBLinExpr in_v = GRBLinExpr();
            
            for(auto i: graph) {
                if (i.find(v) != i.end())
                    in_v += i[v];
            }
            
            model.addConstr(in_v <= 1 , "c1");
        }
        
        // restrição de conservação do fluxo
        // para cada vertice v (diferente de source e target), soma todas as arestas que saem de v e soma todas as arestas que entram em v. a subtração dessas duas somas deve ser igual a zero.
        for(int v = 0; v < graph.size(); v++) {
            if (v == source || v == target)
                continue;
            
            GRBLinExpr in_v = GRBLinExpr();
            GRBLinExpr out_v = GRBLinExpr();
            
            for(auto j: graph[v]) {
                out_v += j.second;
            }
            
            for(auto i: graph) {
                if (i.find(v) != i.end())
                    in_v += i[v];
            }
            
            model.addConstr(out_v - in_v == 0 , "c2");
        }
            
        // atualiza o modelo
        model.update();
        
        // resolve o modelo
        model.optimize();
        
        // apresenta o valor das variaveis
        for(auto v: graph) {
            for(auto i: v) {
                cout << (i.second).get(GRB_StringAttr_VarName) << " " << (i.second).get(GRB_DoubleAttr_X) << endl;
            }
        }
        
        // valor final
        cout << "Latencia Total: " << model.get(GRB_DoubleAttr_ObjVal) << endl;
        
    } catch(GRBException e) {
        cout << "Error code = " << e.getErrorCode() << endl;
        cout << e.getMessage() << endl;
    } catch(...) {
        cout << "Exception during optimization" << endl;
    }
    
    return 0;
}
