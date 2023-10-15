#include <iostream>
#include <vector>

using namespace std;

class Heap {
private:
    // Deklarace a inicializace vektoru pro uchov�n� prvk� haldy (Max Heap)
    vector<int> heap;

    // Funkce pro prohozen� hodnot dvou prom�nn�ch (a, b)
    void swap(int& a, int& b)
    {
        int temp = a;

        a = b;

        b = temp;
    }


    // Funkce pro sestaven� haldy (Heapify) odshora dol�, po��naje ko�enem na indexu 'root_index'
    void heapify_down(int root_index)
    {
        // Vypo��t�n� index� lev�ho a prav�ho potomka uzlu na indexu 'root_index'
        int left_child_index = 2 * root_index + 1;
        int right_child_index = 2 * root_index + 2;

        // Inicializace 'largest' jako index ko�enov�ho uzlu
        int largest = root_index;

        // Porovn�n� hodnoty ko�enov�ho uzlu s hodnotami jeho lev�ho a prav�ho potomka,
        // pokud potomci existuj� a pokud jsou v�t�� ne� ko�enov� uzel
        if (left_child_index < heap.size() && heap[left_child_index] > heap[largest])
        {
            largest = left_child_index;
        }

        if (right_child_index < heap.size() && heap[right_child_index] > heap[largest])
        {
            largest = right_child_index;
        }

        // Pokud byl nejv�t�� prvek nalezen mezi potomky, provede se prohozen� ko�enov�ho uzlu s nejv�t��m potomkem
        // a rekurzivn� se pokra�uje dol� ve stromu, aby se zajistila vlastnost haldy
        if (largest != root_index)
        {
            swap(heap[root_index], heap[largest]);
            heapify_down(largest);
        }
    }

    // Funkce pro sestaven� haldy (Heapify) odspodu nahoru, za��naje uzlem na indexu 'child_index'
    void heapify_up(int child_index)
    {
        // V�po�et indexu rodi�e pro uzlu na indexu 'child_index'
        int root_index = (child_index - 1) / 2;

        // Porovn�n� hodnoty uzlu na indexu 'child_index' s hodnotou jeho rodi�e (na indexu 'root_index')
        // Pokud je hodnota uzlu v�t�� ne� hodnota rodi�e a z�rove� nen� na ko�enov�m uzlu (index 0), provede se prohozen�
        if (child_index > 0 && heap[child_index] > heap[root_index])
        {
            swap(heap[child_index], heap[root_index]);

            // Rekurzivn� vol�n� funkce pro sestaven� haldy sm�rem nahoru
            // Provede se, dokud je cel� strom v souladu s vlastnostmi haldy
            heapify_up(root_index);
        }
    }


public:
    // Konstruktor
    Heap() {}

    // Vlo�en� prvku do haldy
    void insert(int value)
    {
        heap.push_back(value);

        // Z�sk�n� indexu pr�v� vlo�en�ho prvku
        int index = heap.size() - 1;
        // Proveden� operace heapify_up pro obnovu vlastnosti Max Heapu
        heapify_up(index);
    }

    // Odeb�r�n� nejv�t��ho prvku (ko�en haldy)
    int remove() 
    {
        if (heap.empty()) 
        {
            throw runtime_error("Halda je pr�zdn�");
        }

        // Ulo�en� hodnoty ko�enov�ho prvku (nejv�t��ho prvku)
        int root = heap[0];

        // Ulo�en� hodnoty posledn�ho prvku
        int last = heap.back();

        // Nahrazen� ko�enov�ho prvku posledn�m prvkem
        heap[0] = last;

        // Odebr�n� posledn�ho prvku (nejv�t��ho prvku) ze struktury haldy
        heap.pop_back();

        // Proveden� operace heapify_down pro obnovu vlastnosti Max Heapu
        heapify_down(0);

        // Vr�cen� odebran�ho ko�enov�ho prvku
        return root;
    }


    // Velikost haldy
    int size() const 
    {
        return heap.size();
    }

    // Zkontrolovat, zda je halda pr�zdn�
    bool is_empty() const 
    {
        return heap.empty();
    }

    // Vytisknout obsah haldy
    void print() const 
    {
        for (int i = 0; i < heap.size(); ++i) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Heap max_heap;

    max_heap.insert(10);
    max_heap.insert(5);
    max_heap.insert(17);
    max_heap.insert(8);
    max_heap.insert(12);

    cout << "Max Heap: ";
    max_heap.print();
    cout << "Aktualni velikost haldy: " << max_heap.size() << endl;
    cout << "-------------------------------------" << endl;

    while (!max_heap.is_empty()) {
        int max = max_heap.remove();
        cout << "Odebiram " << max << ", Max Heap: ";
        max_heap.print();
        cout << "Aktualni velikost haldy: " << max_heap.size() << endl;
        cout << "-------------------------------------" << endl << endl;
    }


    return 0;
}
