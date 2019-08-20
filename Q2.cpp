#include<bits/stdc++.h>
using namespace std;

/**
* @brief Structure to define the node1 for linked list.
*/

struct node1
{
	/** Value stored in node */
	int data;
	/** Pointer to next node */
	node1 * next = NULL;
};

/**
* @brief Structure to define the linked list.
*/

struct LL
{
	/** Head node pointer of linked list */
	node1 * head;
	/** Size of linked list */
	int size;
	LL()
	{
		size = 0;
	}
	/** Function to insert data in linked list.
	* @param dat Value to be inserted
	*/
	void insert(int dat)
	{
		node1 * insertion = new node1;
		insertion->data = dat;
		if(size==0)
		{
			head = insertion;
		}
		else
		{
			node1 * temp = head;
			while(temp->next)
			{
				temp = temp->next;
			}
			temp->next = insertion;
		}
		size++;
	}
	
	/** Function to get ith index value in linked list.
	* @param i Index value
	*/
	int getindex(int i)
	{
		if(i>size-1 || i>=size) return -1;
		else
		{
			node1 * temp = head;
			for(int j=0;j<i;j++) temp = temp->next;
			return temp->data;
		}
	}
	
	/** Function to display linked list.
	*/
	void display()
	{
		node1 * temp = head;
		while(temp)
		{
			cout<<temp->data<<"->";
			temp = temp->next;
		}
	}
};

int main()
{
	clock_t start,end;
	start = clock();
	LL data;
	LL XOR;
	int n;
	int count = 0;
    cin>>n;
    XOR.insert(0);
    data.insert(0);
    for(int i=1;i<=n;i++)
    {
    	int val;
    	cin>>val;
    	data.insert(val);
    	XOR.insert(val^XOR.getindex(i-1));
    }
    for(int i=1;i<=n;i++)
    {
        for(int k=i;k<=n;k++)
        {
            for(int j=i;j<=k;j++)
            {
                if(j-1>=i)
                {
                    if(XOR.getindex(j-1)^XOR.getindex(i-1) == XOR.getindex(k)^XOR.getindex(j-1))
                    {
                    	count++;
                    	cout<<"("<<i<<","<<j<<","<<k<<")"<<endl;
					}
                }
            }
        }
    }
    cout<<"Total number of triplets are "<<count<<"."<<endl;
    end = clock();
    cout<<"Total CPU time is: "<<float(end-start)/CLOCKS_PER_SEC<<" seconds.";
    return 0;
}

