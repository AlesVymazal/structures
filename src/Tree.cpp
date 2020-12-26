#include "Tree.h"


template <typename T> 
Node<T>::Node(const T data) : data_(data), right_(nullptr), left_(nullptr) {}

template <typename T> 
Node<T>::~Node(){}

template <typename T> 
BST<T>::BST() : root_(nullptr) {}

template <typename T> 
BST<T>::BST(const BST &other)
{
	root_ = new Node<T>(other.root_->data_);
	std::queue<const Node<T>*> nodesToProcess;
  	nodesToProcess.push(other.root_);
  	std::vector<T> values;
    while (!nodesToProcess.empty()) {
    const auto& nodeFront = nodesToProcess.front();
    	
      if (nodeFront->left_) {
      	values.push_back(nodeFront->left_->data_);
        nodesToProcess.push(nodeFront->left_.get());
      }
      if (nodeFront->right_) {
      	values.push_back(nodeFront->right_->data_);
        nodesToProcess.push(nodeFront->right_.get());
      }
    nodesToProcess.pop();

  } 
    for(auto v : values)
    {
    	insert(v);
    }// while*/
}

template <typename T> 
BST<T>::~BST()
{
	delete root_;
}

template <typename T> 
void BST<T>::insert(const T data)
{
    if(root_)
    {
        Node<T> *temp = root_;
        Node<T> *first = temp;

        while(true)
        {
            if(temp->data_ < data && temp->right_)
            {
                temp = temp->right_.get();
            }

            if(temp->data_ > data && temp->left_)
            {
                temp = temp->left_.get();
            }
            if(temp->data_ < data && !temp->right_)
            {
                temp->right_ = std::move(std::make_unique<Node<T>>(data));
                break;
            }
            if(temp->data_ > data && !temp->left_)
            {
                temp->left_ = std::move(std::make_unique<Node<T>>(data));
                break;
            }
        }
        root_ = first;
    }
    else
    {
        root_ = new Node<T>(data);
    }
}

template <typename T> 
std::tuple<Node<T>*, Node<T>*, char, char> BST<T>::find(const int data) const
{
	if(root_)
    {
        Node<T> *temp = root_;
        Node<T> *previous = temp;
        char tmp = ' ';
        char prev = ' ';
        while(true)
        {
        	if(temp->data_ == data)
        	{
        		if(temp->right_ && !temp->left_)
        		{
        			tmp = 'r';
        		}
        		if(temp->left_ && !temp->right_)
        		{
        			tmp = 'l';
        		}
        		if(temp->right_ && temp->left_)
        		{
        			tmp = 'b';
        		}
        		if(!temp->right_ && !temp->left_)
        		{
        			tmp = 'n';
        		}
        		return std::make_tuple(temp,previous,tmp,prev);
        	}
            if(temp->data_ < data && temp->right_)
            {
            	prev = 'r';
            	previous = temp;
                temp = temp->right_.get();
            }
            if(temp->data_ > data && temp->left_)
            {
            	prev = 'l';
            	previous = temp;
                temp = temp->left_.get();
            }
            if(temp->data_ < data && !temp->right_)
            {
                return std::make_tuple(nullptr,temp,' ',' ');
            }
            if(temp->data_ > data && !temp->left_)
            {  
                return std::make_tuple(nullptr,temp,' ',' ');
            }
        }
    }
    return std::make_tuple(nullptr, nullptr,' ',' ');
}

template <typename T> 
bool BST<T>::contains(const T data) const 
{
	Node<T> *temp;
	std::tie(temp, std::ignore, std::ignore, std::ignore) = find(data);
	if(temp)
	{
		return true;
	}
	return false;
}

template <typename T> 
void BST<T>::remove(const T data) {
	Node<T> *temp;
    Node<T> *previous;
    char tmp;
    char prev;
	std::tie(temp, previous, tmp, prev) = find(data);
	std::cout << previous->data_ << " " << temp->data_ << " " << prev << " " << tmp << std::endl;
	if(tmp == 'r' && prev == 'r')
	{
		previous->right_ = std::move(temp->right_);
	}
	if(tmp == 'l' && prev == 'r')
	{
		previous->right_ = std::move(temp->left_);
	}
	if(tmp == 'r' && prev == 'l')
	{
		previous->left_ = std::move(temp->right_);
	}
	if(tmp == 'l' && prev == 'l')
	{
		previous->left_ = std::move(temp->left_);
	}
	if(tmp == 'n' && prev == 'l')
	{
		previous->left_ = std::move(nullptr);
	}
	if(tmp == 'n' && prev == 'r')
	{
		previous->right_ = std::move(nullptr);
	}
	if(tmp == 'b' && prev == 'l')
	{

		Node<T>* smallest = temp->right_.get();
		Node<T>* parent = temp;
		if(smallest->left_)
		{

			while(smallest->left_)
			{
				parent = smallest;
				smallest = smallest->left_.get();
			}
			previous->left_->data_ = smallest->data_;
			if(parent->left_->right_)
			{
				parent->left_ = std::move(parent->left_->right_);
			}
			else
			{
				parent->left_ = std::move(nullptr);
			}	
		}
		else
		{
			previous->left_->data_ = smallest->data_;
			parent->right_ = std::move(nullptr);
		}
		
	}
	if(tmp == 'b' && prev == 'r')
	{
		Node<T>* smallest = temp->right_.get();
		Node<T>* parent = temp;
		if(smallest->left_)
		{
			while(smallest->left_)
			{
				parent = smallest;
				smallest = smallest->left_.get();
			}
			previous->right_->data_ = smallest->data_;
			if(parent->left_->right_)
			{
				parent->left_ = std::move(parent->left_->right_);
			}
			else
			{
				parent->left_ = std::move(nullptr);
			}		
		}
		else
		{
			previous->right_->data_ = smallest->data_;
			parent->right_ = std::move(nullptr);
		}
	}
	return;
}

template <typename T> 
void BST<T>::printBFS() const {
  // Pouzijeme frontu. Na zacatku vlozime do fronty koren a potom opakujeme toto:
  // Dokud neni fronta prazdna
  // {
  //   - podivej se na prvni uzel ve fronte (nodeFront)
  //   - vytiskni jeho hodnotu
  //   - pokud ma nodeFront leveho potomka, vytiskni ho a vloz na konec fronty, protoze
  //     musime zpracovat jeho potomky
  //   - pokud ma nodeFront praveho potomka, vytiskni ho a vloz na konec fronty, protoze
  //     musime zpracovat jeho potomky
  //   - vyjmi nodeFront z fronty pomoci nodesToProcess.pop(), protoze uz ho nebudeme potrebovat
  // }
  // Promenne se ve fronte posunuji z jednoho konce na druhy - hodnota, ktera byla vlozena prvni,
  // bude take prvni vyjmuta (jako kdyz mas trubku, do ktere na jedne strane vkladas micky a na
  // druhe strane vypadavaji - micek, ktery jsi vlozil prvni, vyjede jako prvni na druhe strane
  // a ostatni ho nasleduji - FIFO)
  // BFS VYTISKNE UZLY PO VRSTVACH
  std::queue<const Node<T>*> nodesToProcess;
  nodesToProcess.push(root_);

  while (!nodesToProcess.empty()) {
    const auto& nodeFront = nodesToProcess.front();
    std::cout << "Node " << nodeFront->data_ << ": ";
    if (nodeFront->left_.get() || nodeFront->right_.get()) {
      std::cout << "children ";
      if (nodeFront->left_) {
        std::cout << " " << nodeFront->left_.get()->data_;
        nodesToProcess.push(nodeFront->left_.get());
      }
      if (nodeFront->right_) {
        std::cout << " " << nodeFront->right_.get()->data_;
        nodesToProcess.push(nodeFront->right_.get());
      }
    } else {
      std::cout << "leaf";
    }
    std::cout << std::endl;
    nodesToProcess.pop();
  } // while
}

template <typename T> 
void BST<T>::printDFS() const {
  // Pouzijeme zasobnik. Na zacatku vlozime do zasobniku koren a potom opakujeme toto:
  // Dokud neni zasobnik prazdny
  // {
  //   - podivej se na prvni uzel v zasobniku (nodeFront)
  //   - vytiskni jeho hodnotu
  //   - pokud ma nodeFront leveho potomka, vytiskni ho a vloz na vrcholek zasobniku, protoze
  //     musime zpracovat jeho potomky
  //   - pokud ma nodeFront praveho potomka, vytiskni ho a vloz na vrcholek zasobniku, protoze
  //     musime zpracovat jeho potomky
  //   - vyjmi nodeFront ze zasobniku pomoci nodesToProcess.pop(), protoze uz ho nebudeme potrebovat
  // }
  // Promenne se v zasobniku chovaji podle system LIFO (Last In, First Out) - hodnota, ktery jsi
  // vlozil jak posledni, bude pripravena jako prvni k vyjmuti  (jako kdyz mas trubku, ktera je na
  // jedne strane ucpana. Kdyz vlozis micek A, za nim B a nakonec C, tak A je zcela naspodu, takze
  // kdyz chces nejaky micek vytahnout, musis nejdriv vzit C, potom B a az nakonec A) BFS VYTISKNE
  // UZLY TAK, ZE JDE NAPRED Z KORENE AZ DO LISTU, POTOM SE VRATI NAHORU A POKRACUJE PO SOUSEDNI
  // VETVI DO DALSIHO LISTU ATD.
  std::stack<const Node<T>*> nodesToProcess;
  nodesToProcess.push(root_);

  while (!nodesToProcess.empty()) {
    const auto& nodeTop = nodesToProcess.top();
    const auto childLeft = nodeTop->left_.get();
    const auto childRight = nodeTop->right_.get();

    std::cout << "Node " << nodeTop->data_ << ": ";
    // Nez vlozime leveho nebo praveho potomka, musime vyjmout existujici uzel - uz nebude potreba
    nodesToProcess.pop();

    if (childLeft || childRight) {
      std::cout << "children ";
      if (childLeft) {
        std::cout << " " << childLeft->data_;
        nodesToProcess.push(childLeft);
      }
      if (childRight) {
        std::cout << " " << childRight->data_;
        nodesToProcess.push(childRight);
      }
    } else {
      std::cout << "leaf";
    }
    std::cout << std::endl;
  } // while
}

template <typename T> 
void BST<T>::save(const std::string& filename) const {
  std::ofstream file;
  file.open(filename);
  file << "digraph D {\n";
  file << "\tlabel = \"Binary tree\";\n";
  file << "\tlabelloc = \"t\";\n";
  std::queue<const Node<T>*> nodesToProcess;
  nodesToProcess.push(root_);
  int size = 0, num = 0, count = 0;
  std::vector<int> edges;
  while (!nodesToProcess.empty()) {
    const auto& nodeFront = nodesToProcess.front();
    file << "node" << count++ << " [shape=circle, label=" << nodeFront->data_ << "]" << std::endl;
    if (nodeFront->left_.get() || nodeFront->right_.get()) {
      if (nodeFront->left_) {
      	size++;
      	edges.push_back(num);
        nodesToProcess.push(nodeFront->left_.get());
      }
      if (nodeFront->right_) {
      	size++;
      	edges.push_back(num);
        nodesToProcess.push(nodeFront->right_.get());
      }
    }
    num++;
    size = 0;
    nodesToProcess.pop();
  }
  for(int i = 0; i < edges.size(); ++i)
  {
  	file << "node" << edges[i] << " -> " <<  "node" << i + 1 << std::endl;
  }
  file << "}";
}