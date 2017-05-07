#include<iostream>
#include<vector>
#include<ctime>

using namespace std;

#define INF 99999999

struct retType {
	int returnValue;
	double time;
};

// 선형시간 알고리즘을 이용하여 힙을 생성한다.
// h : 힙을 만들 데이터들이 있는 배열(벡터), N : 서브트리의 루트노드 index, depth : N의 깊이.
void constructHeap(vector<int>& h, int N, int depth);

// 작은 값을 만날 때까지 자식들과 비교하며 downHeap 한다.
int fixHeap(vector<int>& h, int N, int heapSize, int depth);

int fixHeapFast(vector<int>& h, int N, int heapSize, int height);
void bubbleUpHeap(vector<int>& h, int vacParent);

//heap을 출력한다. 디버깅용 함수.
void printHeap(vector<int>& h);

// heapSort를 실행한다. M1번째로 큰 수를 힙에서 삭제한 뒤 fixHeap할 때
// fixHeap을 마지막으로 호출한 노드의 depth를 출력.
retType heapSort(vector<int> h, int M1);

// 빠른 heapSort를 한다. fixHeap이 아닌 fixHeapFast를 이용.
// M2번째로 큰 수를 찾을 때 첫 번째 bubbleUpHeap을 발생하는 위치에 원래 저장되어있던 값을 출력.
// bubbleUpHeap이 발생하지 않을 경우 0을 출력.
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
	// 힙을 구성한다.
	constructHeap(h, 1, 0);


	// 최대값부터 pop하여 힙의 마지막 요소와 swap하고
	// fixHeap하여 다시 힙으로 만들어준다.

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

// 오른쪽, 왼쪽 중 큰 child를 return.
// child가 없으면 -1 return.
int getBig(vector<int>& h, int N, int heapSize)
{
	int left = 2 * N;
	int right = left + 1;
	// 오른쪽 child가 없으면
	if (right > heapSize)
	{
		// left child가 없으면
		if (left > heapSize)
		{
			// 둘다 없으므로 return -1;
			return -1;
		}
		// 오른쪽만 없으면 왼쪽과 비교.
		else
			return left;
	}
	// 양쪽 child가 있으면 큰쪽과 비교.
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
		// 내가 leaf이면
		return -1;
	}

	else if (right == 2)
	{
		// 오른쪽이 없으면 왼쪽과 비교.
		if (h[N * 2] > h[N])
		{
			return 0;
		}
		else
			return 1;
	}
	else // 양쪽 다 있으면
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
	
	//leaf 노드일 때. 
	if (big == -1)
		return depth;

	// child가 더 크면 내려간 후 자식과 비교.
	if (h[N] < h[big])
	{
		swap(h[N], h[big]);
		// nextBig은 자식들 중 큰 것.
		int nextBig = getBig(h, big, heapSize);;

		// 내려간 후 자식이 없으면 더이상 fixHeap을 하지 않는다.
		if (nextBig == -1)
		{
			return depth;
		}
		// 내려간 후 자식이 있지만 child보다 크면 fixHeap을 하지 않는다.
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
	{ // height가 홀수이면 hStop은 height/2를 올림한 위치로 한다.
		hStop = height / 2 + 1;
	}
	else
	{ // height가 짝수이면 hStop은 height/2로 한다.
		hStop = height / 2;
	}

	//printHeap(h);

	int vacStop = promote(h, N, hStop, height, heapSize);
	
	// vacStop
	int vacParent = vacStop / 2;

	// 부모가 더 작으면 bubbleUpHeap
	if (h[vacParent] < h[vacStop])
	{
		swap(h[vacParent], h[vacStop]);
		bubbleUpHeap(h, vacParent);
		return h[vacStop];
	}
	// 그렇지 않으면 fixHeapFast
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