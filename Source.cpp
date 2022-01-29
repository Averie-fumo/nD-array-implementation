#include <iostream>
using namespace std;

template <typename T>
class ndArray
{
private:
	int num = 1;
	int dimen;
	int* dimensionArray;
	T* array;
public:
	ndArray()
	{
		int dimension;
		cout << "No. of dimensions: " << endl;
		cin >> dimension;
		cout << "Enter dimensions:" << endl << "(highest to lowest)" << endl;
		this->dimen = dimension;
		dimensionArray = new int[dimension];
		for (int i = 0; i < dimension;i++)
		{
			cin >> dimensionArray[i];
			num *= dimensionArray[i];
		}
		array = new T[num];
	}
	ndArray(ndArray const& obj)
	{
		num = obj.num;
		array = new T[num];
		dimen = obj.dimen;
		dimensionArray = new int[dimen];

		for (int i = 0; i < dimen;i++)
		{
			dimensionArray[i] = obj.dimensionArray[i];
		}

		for (int i = 0; i < num;i++)
		{
			array[i] = obj.array[i];
		}
	}
	void insertAllElements()
	{
		cout << "Enter elements: " << endl;
		for (int i = 0;i < num;i++)
		{
			cin >> array[i];
		}
	}
	int findIndex()
	{
		int* indexArray = new int[dimen];
		int input, temp, index = 0;

		cout << "Example [ 2 3 ] -- index of 3 is 0 1." << endl;
		cout << "Enter index:" << endl;
		for (int i = 0;i < dimen;i++)
		{
			cin >> indexArray[i];
		}
		for (int i = dimen - 1, j = 0; i >= 0;i--, j++)
		{
			temp = 1;
			for (int k = j, l = dimen - 1; k > 0;k--, l--)
			{
				temp = temp* dimensionArray[l];
			}
			temp *= indexArray[i];
			index = index + temp;
		}
		delete[] indexArray;
		indexArray = nullptr;
		return index;
	}
	void insertElement()
	{
		T element;
		cout << "Enter Element to be inserted:" << endl;
		cin >> element;
		*(array + findIndex()) = element;

	}
	void deleteElement()
	{
		int index = findIndex();
		for (int i = index; i < num - 1; i++)
		{
			array[i] = array[i + 1];
		}
		array[num - 1] = NULL ;

	}
	void extendArray()
	{
		T* temp = new T[num];

		for (int i = 0; i < num;i++)
			temp[i] = array[i];

		delete[] array;
		array = nullptr;

		array = new T[num * 2];
		for (int i = 0; i < num;i++)
		{
			array[i] = temp[i];
		}
		num *= 2;
		dimensionArray[0] *= 2;
		delete[] temp;
		temp = nullptr;
	}
	void shrinkArray()
	{
		T* temp = new T[num];

		for (int i = 0; i < num;i++)
			temp[i] = array[i];

		delete[] array;
		array = nullptr;
		dimensionArray[0] /= 2;
		for (int i = 0; i < dimen;i++)
		{
			num *= dimensionArray[i];
		}
		array = new T[num];
		for (int i = 0; i < num;i++)
		{
			array[i] = temp[i];
		}
		delete[] temp;
		temp = nullptr;
	}
	T retrieveElement()
	{
		return *(array + findIndex());
	}
	T& operator[] (int i) {
		return array[i];
	}
	T& operator()(int i, int j) {
		int index = i * dimensionArray[1] + j;
		return array[index];
	}
	T& operator()(int i, int j, int k)
	{
		int index = (i * dimensionArray[dimen - 2] * dimensionArray[dimen - 1]) + (j * dimensionArray[dimen - 1]) + k;
		return array[index];
	}
	T& operator()(int i, int j, int k, int l)
	{
		int index = (i * dimensionArray[dimen - 3] * dimensionArray[dimen - 2] * dimensionArray[dimen - 1])+ (j * dimensionArray[dimen - 2] * dimensionArray[dimen - 1]) + (k * dimensionArray[dimen - 1]) + l;
		return array[index];
	}
	T& operator()()
	{
		return *(array + findIndex());
	}
	T& operator()(int arr[]) {
		return array[arr[1]];
	}
	friend ostream& operator<< (ostream& os, const ndArray& obj)
	{
		if (obj.dimen <= 3)
		{
			if (obj.dimen == 1)
			{
				for (int i = 0; i < obj.num; i++)
				{
					cout << *(obj.array + i) << " ";
				}
			}
			else if (obj.dimen == 2)
			{
				for (int i = 0; i < obj.dimensionArray[0]; i++)
				{
					for (int j = 0; j < obj.dimensionArray[1]; j++)
					{
						cout << *(obj.array + i * obj.dimensionArray[1] + j) << " ";
					}
					cout << endl;
				}
			}
			else
			{
				for (int i = 0; i < obj.dimensionArray[0]; i++)
				{
					for (int j = 0; j < obj.dimensionArray[1]; j++)
					{
						for (int k = 0; k < obj.dimensionArray[2]; k++)
						{
							cout << *(obj.array + i * obj.dimensionArray[1] * obj.dimensionArray[2] + j * obj.dimensionArray[2] + k) << " ";
						}
						cout << endl;
					}
					cout << endl;
				}
			}
		}
		else
		{
			for (int i = 0; i < obj.num; i++)
			{
				cout << obj.array[i] << " ";
			}
		}
		return os;
	}
	~ndArray()
	{
		delete[] dimensionArray;
		delete[] array;
		dimensionArray = nullptr;
		array = nullptr;
	}
};
int main()
{
	ndArray<char> array;

	cout << "---INSERTING ALL ELEMENTS---" << endl;
	array.insertAllElements();
	
	cout << endl << "Array: " << endl;
	cout << "--- << OPERATOR OVERLOADING---" << endl;
	cout << array << endl;

	cout << "---RETRIVING ELEMENT---" << endl;
	cout << array.retrieveElement() << endl;

	cout << "---DELETING ONE ELEMENT---" << endl;
	array.deleteElement();
	cout << endl << "Array: " << endl;
	cout << array << endl;

	cout << "---INSERTING ONE ELEMENT---" << endl;
	array.insertElement();
	cout << endl << "Array: " << endl;
	cout << array << endl;

	cout << "---DOUBLING THE ARRAY SIZE---" << endl;
	array.extendArray();
	array.insertAllElements();
	cout << endl << array;

	cout << "---SHRINKING THE ARRAY BACK---" << endl;
	array.shrinkArray();
	cout << array;

	cout << "---MAKING NEW ARRAY---" << endl;
	ndArray<char> array1(array);
	cout << array1;

	return 0;
}
