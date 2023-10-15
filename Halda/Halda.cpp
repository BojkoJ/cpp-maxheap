#include <iostream>
#include <vector>

using namespace std;

class Heap {
private:
    // Deklarace a inicializace vektoru pro uchování prvkù haldy (Max Heap)
    vector<int> heap;

    // Funkce pro prohození hodnot dvou promìnných (a, b)
    void swap(int& a, int& b)
    {
        int temp = a;

        a = b;

        b = temp;
    }


    // Funkce pro sestavení haldy (Heapify) odshora dolù, poèínaje koøenem na indexu 'root_index'
    void heapify_down(int root_index)
    {
        // Vypoèítání indexù levého a pravého potomka uzlu na indexu 'root_index'
        int left_child_index = 2 * root_index + 1;
        int right_child_index = 2 * root_index + 2;

        // Inicializace 'largest' jako index koøenového uzlu
        int largest = root_index;

        // Porovnání hodnoty koøenového uzlu s hodnotami jeho levého a pravého potomka,
        // pokud potomci existují a pokud jsou vìtší než koøenový uzel
        if (left_child_index < heap.size() && heap[left_child_index] > heap[largest])
        {
            largest = left_child_index;
        }

        if (right_child_index < heap.size() && heap[right_child_index] > heap[largest])
        {
            largest = right_child_index;
        }

        // Pokud byl nejvìtší prvek nalezen mezi potomky, provede se prohození koøenového uzlu s nejvìtším potomkem
        // a rekurzivnì se pokraèuje dolù ve stromu, aby se zajistila vlastnost haldy
        if (largest != root_index)
        {
            swap(heap[root_index], heap[largest]);
            heapify_down(largest);
        }
    }

    // Funkce pro sestavení haldy (Heapify) odspodu nahoru, zaèínaje uzlem na indexu 'child_index'
    void heapify_up(int child_index)
    {
        // Výpoèet indexu rodièe pro uzlu na indexu 'child_index'
        int root_index = (child_index - 1) / 2;

        // Porovnání hodnoty uzlu na indexu 'child_index' s hodnotou jeho rodièe (na indexu 'root_index')
        // Pokud je hodnota uzlu vìtší než hodnota rodièe a zároveò není na koøenovém uzlu (index 0), provede se prohození
        if (child_index > 0 && heap[child_index] > heap[root_index])
        {
            swap(heap[child_index], heap[root_index]);

            // Rekurzivní volání funkce pro sestavení haldy smìrem nahoru
            // Provede se, dokud je celý strom v souladu s vlastnostmi haldy
            heapify_up(root_index);
        }
    }


public:
    // Konstruktor
    Heap() {}

    // Vložení prvku do haldy
    void insert(int value)
    {
        heap.push_back(value);

        // Získání indexu právì vloženého prvku
        int index = heap.size() - 1;
        // Provedení operace heapify_up pro obnovu vlastnosti Max Heapu
        heapify_up(index);
    }

    // Odebírání nejvìtšího prvku (koøen haldy)
    int remove() 
    {
        if (heap.empty()) 
        {
            throw runtime_error("Halda je prázdná");
        }

        // Uložení hodnoty koøenového prvku (nejvìtšího prvku)
        int root = heap[0];

        // Uložení hodnoty posledního prvku
        int last = heap.back();

        // Nahrazení koøenového prvku posledním prvkem
        heap[0] = last;

        // Odebrání posledního prvku (nejvìtšího prvku) ze struktury haldy
        heap.pop_back();

        // Provedení operace heapify_down pro obnovu vlastnosti Max Heapu
        heapify_down(0);

        // Vrácení odebraného koøenového prvku
        return root;
    }


    // Velikost haldy
    int size() const 
    {
        return heap.size();
    }

    // Zkontrolovat, zda je halda prázdná
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
