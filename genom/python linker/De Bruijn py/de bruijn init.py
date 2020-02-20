#import time
#start = time.time()
""" Part1 DBN _ graph initialisation from an fq file"""
class graph:
    """ univers == l'ensemble des sommets unique dans le graphs
        len_univers = nombre de sommets(noeuds / nod ) dans l'univers {index : (k_mer,nbr_d'occurences}
        nbr_occurence = nbr de fois où on avait besoin de crer le noeud 
        The graphs head is the first key in the dictio that has in degree - out degree =1
        -------------------------------------------------------------------------
        arcs_sortant = l'ensemble des arcs sortant d'un sommet comment ça marche?
        arc_sortant[index] =  (index_sortie ,nombre d occurences)
        index = un nombre relatif (dans le dictionnaire univers) à un kmer (voir document)
        représentant le noeud du début 
        index_sortie = l'indexe du kmer représentant le noeud terminale
        ---------------------------------------------------------------------------
        moyenne_ocurrences = reprèsente le nombre moyen d'occurence d'un arc qui sera utiliser pour
        corriger les erreurs
        -----------------------------------------------------------------------------
        arc_entrant = l'ensemble des arcs entrant dans un sommet :
        arc_entrant[index] = (index_entré , nmbrs d'occurences)
        index = index de l'element voullu // index_entré element dont le noeud terminale est index
        -----------------------------------------------------------------------------
        on implemente la liste arc_entrant pour gangner en complexité temporelle lors de la recherche
        / correction des erreurs de lectures dans le graph et l'équilibrer par après
        """
    def __init__(self):
        self.univers = {}
        self.len_univers = 0
        self.arcs_sortant = []
        #the form of arcs_sortant list is:
        #[liste des arcs sortant de element i] --> elti = [[noeud_terminal(target nod) , nombre d occurences]]
        #arcs_entrant
        self.arcs_entrant = []
        self.moyenne_occurences = 0


    def afficher(self):
        print("universe: {}".format(self.univers))
        print("universe: {}".format(self.arcs_sortant))
        print("universe: {}".format(self.arcs_entrant))

    def kmer_in_universe(self,kmer):
        #searches if there's a corresponding nod (index is the keys) with the k_mer as it's items
        for i in range(self.len_univers):
            if self.univers[i][0] ==kmer:
                return (True,i) #i est la postion du sommet dans l'univers
        return (False,0)

    def append_nod(self,kmer):
        #adds a nod to the universe
        last = self.len_univers
        bool_ , idx =self.kmer_in_universe(kmer)
         #le faite d'ajouter un noeud (existant ou non)<-> ajouter 1 au nombre d'occurences totale de tout les noeuds du graph
        self.moyenne_occurences += 1;
        if bool_== False:
            self.univers[last] = [kmer,1]#adds the k_mer to the universe
            self.len_univers += 1    #adds 1 to the legnth of the universe
            #on ajoute une liste d'arc de cet element
            self.arcs_sortant.append([]) 
            self.arcs_entrant.append([])
            return True #the append has been done
        else:
            self.univers[idx][1] +=1
            return False #append not done
    
    def increment_poids_arclist(self , pos_kmer1 , pos_kmer2):
        """ increments le poids of (pos_kmer2,poids) in the element pos_kmer1 arc_sortant list
        and symetrically increments le poids of (pos_kmer1,poids) in the element pos_kmer2 arc_entrant list"""

        lis_sortant = self.arcs_sortant[pos_kmer1]
        lis_entrant = self.arcs_entrant[pos_kmer2]
        for elt_sortant in lis_sortant:
            if elt_sortant[0] == pos_kmer2:
                #by symetry if kmer1-->kmer2 (kmer2 is arc sortant existant) then same for entrant pour kmer1 
                elt_sortant[1] += 1

                for elt_entrant in lis_entrant:
                    """doing this adds less complexity when compared to a loop trought all element of arc_sortant in order
                    to replace 2 nods (replace les noeuds entrant // sortant) de O(N²) to O(N)"""
                    if elt_entrant[0] == pos_kmer1:
                        elt_entrant[1] +=1
                        return True
        return False

    def add_arc_magical(self,imbalanced_noeud_index,mode):
        """ special case of add_arc"""
        len_universe = self.len_univers
        #magical node is always the last node!! (used in balancing the graph) just to win a bit in complexity
        if mode =="out":
            pos_kmer1 = len_universe-1
            pos_kmer2 = imbalanced_noeud_index
        if mode == "in":
            pos_kmer1 = imbalanced_noeud_index
            pos_kmer2 = len_universe-1

        poids_flag = increment_poids_arclist(self,pos_kmer1 , pos_kmer2)
        if poids_flag == False:
            self.arcs_sortant[pos_kmer1].append([pos_kmer2,1])
            self.arcs_entrant[pos_kmer2].append([pos_kmer1,1])

    def add_arc(self,kmer1,kmer2):
        '''neeeds some optimisation (instead of using kmers we gonna use direclty their indexe)'''
        bool1 = self.append_nod(kmer1)
        bool2 = self.append_nod(kmer2)
        len = self.len_univers
        poids_flag = False#means poids =1 (new arc) else means increment poids (existing arc)
        if bool1 == True:
            """kmer1 is the start nod and it's new(just been created) then all arc created has a poids of 1"""
            if bool2 == True:
                #pos_kmer1 = len-2 // pos_kmer2 = len-1
                pos_kmer1 = len- 2
                pos_kmer2 = len- 1
            else:
                #pos_kmer1 = len-1 , pos_kmer2 = i
                pos_kmer1 = len-1
                pos_kmer2 = self.kmer_in_universe(kmer2)[1]
                
        else:
            '''kmer1 already exist so it's arc list is already existing :
            if kmer2 is in that list then poids +=1 else it's a newly added
            terminal nod so poids = 1'''
            pos_kmer1 = self.kmer_in_universe(kmer1)[1]
            if bool2 == True:
                pos_kmer2 = len-1
            else:
                pos_kmer2 = self.kmer_in_universe(kmer2)[1]    
                poids_flag = self.increment_poids_arclist(pos_kmer1,pos_kmer2)
                #even if kmer2 is already an existing nod there's no garenty that it's a terminal nod of kmer1
                #so we need to search for it in the arc_sortant list if it exists (TRUE) then we increment poids
                #of both the arc_lists (sortant et entrant)

        if poids_flag == False:
            #if k_mer1 or k_mer2 are newly created then there's no way that arc already exists
            #wich means we just have to make one
            self.arcs_sortant[pos_kmer1].append([pos_kmer2,1])
            self.arcs_entrant[pos_kmer2].append([pos_kmer1,1])
                

def read_sequence_from_file(fichier):
    """ fichier is a file.txt (or .fq) argument !"""
    fichier.readline()#skips the line: @r1 ...
    seq = fichier.readline()#saves the line containing the sequence
    fichier.readline()# skips the line : +
    fichier.readline()#skips the line : IIIII...
    return seq

def DBN_graph_builder_filemode(k,filename):
    """ k is the parameter used to make the kmers """
    DBN_graph = graph()# creates / initialises the
    fichier = open(filename,"r")
    seq = read_sequence_from_file(fichier)

    while(seq!=""):
        add_sequence_to_graph(DBN_graph,k,seq)
        seq = read_sequence_from_file(fichier)
    fichier.close()
    #on a creer le graph maintenant il faut calculer la moyenne = somme des occurences / nombre de sommets
    DBN_graph.moyenne_occurences = DBN_graph.moyenne_occurences/DBN_graph.len_univers
    #DBN_graph.afficher()
    return DBN_graph

def add_sequence_to_graph(DBN_graph,k,read):
    """ this function get the right and left k-1 mers , adds them to the graph , and links them with an arc
    from left -> right"""
    for start in range(len(read)-k+1):
        k_mer = read[start:start+k:1]
        km_left = k_mer[0:k-1]
        km_right = k_mer[1:k]
        DBN_graph.append_nod(km_left)
        DBN_graph.append_nod(km_right)
        DBN_graph.add_arc(km_left,km_right)
        

#unit test part1 : DONE
#DBN_graph = graph()
#add_sequence_to_graph(DBN_graph ,3 , "AAABBB")
#DBN_graph.afficher()


# k = 60
# DBN_graph_builder_filemode(60,"C:/Users/HP/Desktop/Projex/GENOME/genom/genom/Data/ads1_week4_reads.fq")
#needs about 354s (5 mins) on my PC to create the graph from scratch
#end = time.time()
#print("time : " + str(end-start))
"""             PART2 : Read error correction                             """

def is_brother(kmer_1 , kmer_2, nbr_of_changes):
    """ tests if kmer1 and kmer2 are brothers:
	brothers: means they are the same except for a number of elements (nbr_of_change)
	kmer1 = hello;kmer_2 = hazlo : these 2 are brothers for with a nbr_of_change = 2
    meaning for every i>=2 is_brother(kmer1,kmer2,i) == TRUE
    ----------------------------------------------------------------------------------
    in this case we won't test out the lenght of kmer1 and kmer2 since we suppose they got the same lenght = k"""
    counter = 0 
    for i in range(len(kmer_1)):
        if (kmer_1[i]!=kmer_2[i]):
            counter+=1
            if counter>nbr_of_changes : return False
    return True

def replace_noeud(DBN_graph:graph , index_noeud_destination , index_noeud_source):#needs unit test
    """ cette fonction fait l'union de la liste d'arcs entrant / sortant du noeud dest et source (dans dest) puis supprime le
    noued_source! (isole ce noeud) en premier temps.
    biensure il faut faire la mise à jour des arcs_sortant qui serons changer dans la list_entrant
    exemple: sortant .. 0:[(1,2)] 1:[()] 2:[(0,2)] *** entrant .. 0:[(2,2)] 1:[(0,2)] 2:[()]
    fesons l'union de 0 et 2 :
    étape1: changer 2 par 0 partout ***  0:[(1,2)] 1:[()] 2:[(0,2)] // 0:[(0,2)] 1:[(0,2)] 2:[()] 
    étape2: union of list 0 and 2 & supression de 2 *** 0:[(1,2),(0,2)] 1:[()]     // 0:[(0,2)] 1:[(0,2)]
    ----------------------------------------------------------------------------------------------------------------------------
    en deusième temps la fonction met à jour le dictionnaire univers (elle supprime le noued source)"""
    #étape1
    for i in range(DBN_graph.len_univers) :
        #len of list entrant/sortant is the same as len_universe
        try:
            if DBN_graph.arcs_entrant[i][0] == index_noeud_source:
                DBN_graph.arcs_entrant[i][0] = index_noeud_destination

            if DBN_graph.arcs_sortant[i][0] == index_noeud_source:
                DBN_graph.arcs_sortant[i][0] = index_noeud_destination
        except :#means list[i] = []
            pass
    
    #faire étape2 pour liste_sortant
    list_dst = DBN_graph.arcs_sortant[index_noeud_destination]
    list_src = DBN_graph.arcs_sortant[index_noeud_source]
    for elt_src in list_src:
        flag_exist = 0 #search if elt_src exists in list_dst
        for elt_dst in list_dst:
            if elt_dst[0] == elt_src[0]:
                elt_dst[1] += elt_dst[1]
                flag_exist = 1
                break
        if flag_exist ==0 :
            list_src.append(elt_src)

    del DBN_graph.arcs_sortant[index_noeud_source]
    #faire étape 2 pour liste_entrant
    list_dst = DBN_graph.arcs_entrant[index_noeud_destination]
    list_src = DBN_graph.arcs_entrant[index_noeud_source]
    for elt_src in list_src:
        flag_exist = 0 #search if elt_src exists in list_dst
        for elt_dst in list_dst:
            if elt_dst[0] == elt_src[0]:
                elt_dst[1] += elt_dst[1]
                flag_exist = 1
                break
        if flag_exist ==0 :
            list_src.append(elt_src)

    del DBN_graph.arcs_sortant[index_noeud_source]
    #deusième temps
    del DBN_graph.univers[index_noeud_source]
    DBN_graph.len_univers -= 1

def get_closest_brother(DBN_graph:graph , index_noeud_source ):
    """ add comment!!"""
    kmer = DBN_graph.univers[index_noeud_source][0]
    #item = (key , vallue) key = index / /vallue = [kmer,occurences]
    for item in DBN_graph.univers.items():
        possible_bro = item[1][0]
        if (kmer!=possible_bro and is_brother(kmer,possible_bro,1)):
            return item[0] #returns the key (index of the kmer)
    #si aucun frère n'est trouver on renvoie l'indexe de 
    return index_noeud_source

def replace_noeud_by_bro(DBN_graph:graph, index_noeud_source):
    index_noeud_destination  = get_closest_brother(DBN_graph , index_noeud_source)
    print(index_noeud_destination)
    #on trouve la meilleur destination (possible pas 100% correcte)
    replace_noeud(DBN_graph , index_noeud_destination , index_noeud_source)

def correct_read_errors1cm(DBN_graph):
    """	Return	an	error-corrected	version	of	read.
    k=k-mer	length.	supposing that at max 1 error occurs for each kmer"""
    moyenne = DBN_graph.moyenne_occurences
    #pas besoins de s'interesser au changement sur la moyenne elle ne s'utilise que pour corriger les erreurs rien d'autre
    for key in DBN_graph.univers:
        if DBN_graph.univers[key][1]<moyenne:
            #this maens that that kmer is probably a read error that needs to be changed.
            replace_noeud_by_bro(DBN_graph , key)
        
    

"""             PART3 : Eulerian walk + balancing the graph                             """

""" corriger les erruers reviens aussi à modifier la topographie du graph de façon à rendre le graph semi-eulerien
hypothétiquement un graph de debruijn 'parfait' est toujours eulerien. or avec 1%  d'érreur de lecture on ne peut corriger
au meilleurs des cas que 99,7%  des défaillance topologique de graph donc il faut surtout faire attention car le graph
résultat peut ne pas être eulerian (on fait balancer le graph alors -voir théorie des graphe)
    la méthode pour balancer ke graph est d'ajouter un noued de k_mer vide lié à tout noeud non balancé (sauf les 2 premiers
noeud non balancé trouveé) la façon avec la quelle sont lié dépends du besoins du noued
exemple : deugre entrant du noued = 3 deugre sortant du noued = 5 ( 3-5 = -2 ) donc le noued à besoin de noeud entrant!
on ajoute le noued 3 dans la liste_sortant de "" et "" dans la liste entrant de 3 """
def balance_noeud(DBN_graph : graph , imbalanced_noeud_index:int , in_out_mode:str , difference):
    """ add comment"""
    DBN_graph.append_nod("") #append the magical node (she'll always be the last element in the graph!!)
    DBN_graph.add_arc_magical(imbalanced_noeud_index , in_out_mode)

def balance_graph(DBN_graph : graph):
    """ I made this one it's actually not always usefull (i won't use it tho)
    basically if we use the magic node we can't balance it!! (demonstration to be added) so we must at least leave it
    with |out_deg - in deg | = 1 wich means once we use magical node counter we'll only search for one semi_balanced nod
    (means |out -in| = 1) """
    counter = 0
    in_list = DBN_graph.arcs_entrant
    out_list = DBN_graph.arcs_sortant
    head = -1

    flag_magical_nod = 0 #=1 if we used the magical node 0 else
    last_semi_balanced_nod = -1 #no need to define it but just to know it's there
    counter_limits = 2

    for item in DBN_graph.univers:
        noeud_index = item[0] 
        out_deg = get_degre(out_list[noeud_index][1])
        in_deg  = get_degre(in_list[noeud_index][1])

        if out_deg < in_deg:
            if out_deg - in_deg == -1:
                if counter == 0 and head == -1: head = noeud_index #this state is hit one and only one time!!
                #just a note if head ==-1 after the balancing then the graph has an eulerian cycle wich is fine too
                if counter == 1 and flag_magical_nod ==0: 
                    last_semi_balanced_nod , last_mode = (noeud_index,"out") 
                    #this will be used in case we got 2 semi_balanced nod and we need to add a magical nod
                    #why last? because if we find another semi_balanced node means we'll need magical node
                    #then that "last_semi.." will be the last one to be used (magical node takes it place)
                if counter > counter_limits:
                    #we need a magical node here so we must:
                    #1- balance the last_semi_balanced_nod // counter_limits =1 instead of 2 // flag_magical =1
                    if flag_magical_nod ==0:
                        balance_noued(DBN_graph , last_semi_balanced_nod , last_mode ,1)
                        counter_limits = 1
                        flag_magical_nod = 1
                    balance_noeud(DBN_graph , noeud_index , "out" , 1)
            else:
                balance_noeud(DBN_graph , noeud_index , "out" , in_deg - out_deg)
        
        if out_deg > in_deg:
            if out_deg - in_deg == 1:
                if counter == 0 and head == -1: 
                    head = noeud_index 
                
                if counter == 1 and flag_magical_nod ==0: 
                    last_semi_balanced_nod , last_mode = (noeud_index,"in") 
                    #this will be used in case we got 2 semi_balanced nod and we need to add a magical nod
                if counter > counter_limits:
                    #we need a magical node here so we must:
                    #1- balance the last_semi_balanced_nod // counter_limits =1 instead of 2 // flag_magical =1
                    if flag_magical_nod ==0:
                        balance_noued(DBN_graph , last_semi_balanced_nod , last_mode ,1)
                        counter_limits = 1
                        flag_magical_nod = 1
                    balance_noeud(DBN_graph , noeud_index , "in" , 1)
            else:
                balance_noeud(DBN_graph , noeud_index , "in" , out_deg - in_deg)            

    return head

def eulerian_walk(DBN_graph : graph):
    #head = balance_graph(DBN_graph)
    head = 0
    position = head

    walk = [head]
    list_arcsortant = DBN_graph.arcs_sortant
    track = []
    loop_cond = 1


    while (loop_cond or DBN_graph.arcs_sortant == [] ):
        dead_end = 0
        while ( not dead_end or DBN_graph.arcs_sortant == [] ):
            #get premier noued that has arc with current nod (position) 
            try:
                next_nod = DBN_graph.arcs_sortant[position][0] 
                if next_nod[1]!=0:
                    DBN_graph.arcs_sortant[position][1] -=1
                    track.append(next_nod[0])
                    postion = next_nod[0]
                if next_nod[1] ==0:
                    del DBN_graph.arcs_sortant[position][0]
                    continue
            except: #means DBN_graph.arcs_sortant[position] = [] (vide == dead_end)
                dead_end = 1
        #reset // backtrack and apend to first position in walk if way found reset else
        #go back if the elt found is the head and u blocked then loop_cond = 0 and
        #search for any elemtn left in the arc_sortant list and add them
        for i in range(len(track)-1 ,-1 ,-1):
            if DBN_graph.arcs_sortant[track[i]] !=[]:
                dead_end = 0
                break
            else:
                walk.insert(0,track[i])
        print(track)
        print(walk)
        if dead_end == 1:
            #means there's no other arc_sortant
            loop_cond = 0

    return walk

"""             PART4: Genom assembly __main__ function                                 """

def concatenate(kmer1,kmer2):#gets the char or str that will be added to adn
    if kmer1 == "":
        return kmer2
    if kmer2 == "":
        return ""
    if kmer1!="" and kmer2!="":
        return kmer2[-1] 

def assemble_genom():
    k=3 #get k from interface
    in_file = "test.txt" #get file from interface
    DBN_graph = DBN_graph_builder_filemode(k,in_file)
    DBN_graph.afficher()
    #correct_read_errors1cm(DBN_graph)
    path = eulerian_walk(DBN_graph)
    out_file = "out.txt" #get file from interface
    file = open(out_file , "w")
    file.write(path[0])
    for i in range( len(path) -1 ):
        kmer1 = DBN_graph.univers[path[i]]
        kmer2 = DBN_graph.univers[path[i+1]]
        
        file.write(concatenate(kmer1 , kmer2))
    file.close()

assemble_genom()
