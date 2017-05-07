#include<iostream>
#include<vector>
#include<ctime>

using namespace std;

#define INF 99999999

struct retType {
	int returnValue;
	double time;
};

// �����ð� �˰����� �̿��Ͽ� ���� �����Ѵ�.
// h : ���� ���� �����͵��� �ִ� �迭(����), N : ����Ʈ���� ��Ʈ��� index, depth : N�� ����.
void constructHeap(vector<int>& h, int N, int depth);

// ���� ���� ���� ������ �ڽĵ�� ���ϸ� downHeap �Ѵ�.
int fixHeap(vector<int>& h, int N, int heapSize, int depth);

int fixHeapFast(vector<int>& h, int N, int heapSize, int height);
void bubbleUpHeap(vector<int>& h, int vacParent);

//heap�� ����Ѵ�. ������ �Լ�.
void printHeap(vector<int>& h);

// heapSort�� �����Ѵ�. M1��°�� ū ���� ������ ������ �� fixHeap�� ��
// fixHeap�� ���������� ȣ���� ����� depth�� ���.
retType heapSort(vector<int> h, int M1);

// ���� heapSort�� �Ѵ�. fixHeap�� �ƴ� fixHeapFast�� �̿�.
// M2��°�� ū ���� ã�� �� ù ��° bubbleUpHeap�� �߻��ϴ� ��ġ�� ���� ����Ǿ��ִ� ���� ���.
// bubbleUpHeap�� �߻����� ���� ��� 0�� ���.
retType acceleratedHeapSort(vector<int>h, int M2);

int main()
{
	int T;
	cin >> T;
	for(int i=1; i<=T; i++)
	{
		vector<int> arr;

		int N;
		cin >> N;
		arr.resize(N+1);
		arr[0] = INF;
		for (int i = 1; i <= N; i++)
		{
			cin >> arr[i];
		}
		int M1, M2;
		cin >> M1 >> M2;

		if (i >= 4 && i <= 6)
		{
			retType ori = heapSort(arr, M1);
			retType acc = acceleratedHeapSort(arr, M2);

			cout << ori.returnValue << " " << acc.returnValue << endl;
			cout << ori.time << " " << acc.time << endl;
		}
	}
}

void checkSort(vector<int>& h)
{
	for (int i = 1; i < h.size()-1; i++)
	{
		if (h[i] > h[i + 1])
		{
			cout << "sort fail : " << i << endl;
			return;
		}
	}
	cout << "sort success" << endl;
}

retType heapSort(vector<int> h, int M1)
{
	retType ret;
	clock_t start_time, end_time;

	start_time = clock();

	///////////////////////////////////////////////////////////////////////////////////////////////

	int heapSize = h.size();
	// ���� �����Ѵ�.
	constructHeap(h, 1, 0);


	// �ִ밪���� pop�Ͽ� ���� ������ ��ҿ� swap�ϰ�
	// fixHeap�Ͽ� �ٽ� ������ ������ش�.

	for (int i = heapSize - 1; i > 0; i--)
	{
		swap(h[1], h[i]);
		if (i == 4)
		{
			int tmp = 3 + 5;
		}

		int t = fixHeap(h, 1, i - 1, 0);
		if (i == heapSize - M1 + 1)
		{
			cout << "Let's Go" << endl;
		}
		if (i == heapSize - M1)
			ret.returnValue = t;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	end_time = clock();
	ret.time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	checkSort(h);
	//printHeap(h);
	return ret;
}

retType acceleratedHeapSort(vector<int>h, int M2)
{
	retType ret;
	clock_t start_time, end_time;

	start_time = clock();


	int heapSize = h.size();

	constructHeap(h, 1, 0);

	for (int i = heapSize - 1; i > 0; i--)
	{
		swap(h[1], h[i]);
		int tmp = i - 1;
		int height = -1;
		while (tmp > 0)
		{
			tmp /= 2;
			height++;
		}
		int t = fixHeapFast(h, 1, i - 1, height);
		if (i == heapSize - M2)
			ret.returnValue = t;
	}
	
	end_time = clock();
	ret.time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	
	
	checkSort(h);
	//printHeap(h);
	return ret;
}



void constructHeap(vector<int>& h, int N, int depth)
{
	if (N > h.size() - 1)
	{
		return;
	}

	constructHeap(h, N * 2, depth + 1);
	constructHeap(h, (N * 2) + 1, depth + 1);

	fixHeap(h, N, h.size()-1, depth);
}

// ������, ���� �� ū child�� return.
// child�� ������ -1 return.
int getBig(vector<int>& h, int N, int heapSize)
{
	int left = 2 * N;
	int right = left + 1;
	// ������ child�� ������
	if (right > heapSize)
	{
		// left child�� ������
		if (left > heapSize)
		{
			// �Ѵ� �����Ƿ� return -1;
			return -1;
		}
		// �����ʸ� ������ ���ʰ� ��.
		else
			return left;
	}
	// ���� child�� ������ ū�ʰ� ��.
	else
	{
		return ((h[left] > h[right]) ? left : right);
	}
}

int checkHeap(vector<int>& h, int N, int heapSize)
{
	if (N >= heapSize)
	{
		return 2;
	}
	int left = checkHeap(h, N * 2, heapSize);
	int right = checkHeap(h, N * 2 + 1, heapSize);

	if (left == 0 || right == 0)
		return 0;

	if (left == 2)
	{
		// ���� leaf�̸�
		return -1;
	}

	else if (right == 2)
	{
		// �������� ������ ���ʰ� ��.
		if (h[N * 2] > h[N])
		{
			return 0;
		}
		else
			return 1;
	}
	else // ���� �� ������
	{
		int big = getBig(h, N, heapSize);
		if (h[N] > h[big])
		{
			return 1;
		}
		else
			return 0;
	}
}

int fixHeap(vector<int>& h, int N, int heapSize, int depth)
{
	if (heapSize == 0)
		return 0;
	int big = getBig(h, N, heapSize);
	
	//leaf ����� ��. 
	if (big == -1)
		return depth;

	// child�� �� ũ�� ������ �� �ڽİ� ��.
	if (h[N] < h[big])
	{
		swap(h[N], h[big]);
		// nextBig�� �ڽĵ� �� ū ��.
		int nextBig = getBig(h, big, heapSize);;

		// ������ �� �ڽ��� ������ ���̻� fixHeap�� ���� �ʴ´�.
		if (nextBig == -1)
		{
			return depth;
		}
		// ������ �� �ڽ��� ������ child���� ũ�� fixHeap�� ���� �ʴ´�.
		if (h[big] > h[nextBig])
			return depth;

		return fixHeap(h, big, heapSize, depth+1);
	}
	else
	{
		return depth;
	}
}





int promote(vector<int>& h, int N, int hStop, int height, int heapSize)
{
	int now = N;
	int big;
	for (int i = height; i > hStop; i--)
	{
		
		big = getBig(h, now, heapSize);
		if (big != -1)
		{
			swap(h[now], h[big]);
			now = big;
		}
	}
	return now;
}

void bubbleUpHeap(vector<int>& h, int vac)
{
	int parent = vac / 2;
	if (h[vac] > h[parent])
	{
		swap(h[vac], h[parent]);
		bubbleUpHeap(h, parent);
	}
}


int fixHeapFast(vector<int>& h, int N , int heapSize, int height)
{
	if (height == 0)
		return 0;
	if (height == 1)
	{
		int big = getBig(h, N, heapSize);
		if (big != -1)
		{
			if(h[N] < h[big])
				swap(h[N], h[big]);
		}
		return 0;
	}

	int hStop;
	if (height & 1)
	{ // height�� Ȧ���̸� hStop�� height/2�� �ø��� ��ġ�� �Ѵ�.
		hStop = height / 2 + 1;
	}
	else
	{ // height�� ¦���̸� hStop�� height/2�� �Ѵ�.
		hStop = height / 2;
	}

	//printHeap(h);

	int vacStop = promote(h, N, hStop, height, heapSize);
	
	// vacStop
	int vacParent = vacStop / 2;

	// �θ� �� ������ bubbleUpHeap
	if (h[vacParent] < h[vacStop])
	{
		swap(h[vacParent], h[vacStop]);
		bubbleUpHeap(h, vacParent);
		return h[vacStop];
	}
	// �׷��� ������ fixHeapFast
	else
	{
		return fixHeapFast(h, vacStop, heapSize, hStop);
	}
}


void printHeap(vector<int>& h)
{
	int line = 2;
	int linecount = 7;
	
	for (int i = 1; i < h.size(); i++)
	{
		if (i /line)
		{
			cout << endl;
		
			linecount--;
			line *= 2;
		}
		
	/*	if (h[i] == 0)
		{
			cout<<"0 detected"<<endl;
		}*/

		cout << h[i]<<" ";
		
		
		
	}
	cout << endl;
}