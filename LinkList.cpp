#include <iostream>

struct ListNode{
    int val{};
    ListNode* next{};
};
namespace ListIntersection{
 
    ListNode* getIntersectionNode(ListNode* h1, ListNode* h2){
        if(!h1 || !h2)return nullptr;

        
        ListNode *t1 = h1, *t2 = h2;
        while(t1 != t2){
            t1 = t1 ? t1->next : t2;
            t2 = t2 ? t2->next : t1;
        }

        return t1;
    }
}

namespace ReverseList{

    void reverse(ListNode *s, ListNode *e){
        e = e->next;
        ListNode *pre = {}, *cur = s, *next{};
        while(cur != e){
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        s->next = e;
    }

    ListNode *teamEnd(ListNode *head, int k){
        while(--k != 0 && head){
            head = head->next;
        }
        return head;
    }

    ListNode* reverseKGroup(ListNode *head, int k){
        if(!head || !head->next)return head;

        ListNode *start = head;
        ListNode *end = teamEnd(start, k);
        if(!end)return head;
        head = end;
        reverse(start, end);
        ListNode *lastTeamEnd = start;
        while(lastTeamEnd->next){
            start = lastTeamEnd->next;
            end = teamEnd(start, k);
            if(!end){
                return head;
            }

            reverse(start, end);
            lastTeamEnd->next = end;
            lastTeamEnd = start;
        }

        return head;
    }
}

// namespace CopyList{
//     ListNode *copyList(ListNode *head){
//         if(!head)return nullptr;
//         ListNode *cur = head;
//         while(cur){
//             ListNode *node = new ListNode();
//             node->val = cur->val;
//             node->next = cur->next;
//             cur->next = node;
//             cur = cur->next->next;
//         }

//         cur = head;
//         while(cur){
//             cur->next->random = cur->random->next;
//             cur = cur->next->next;
//         }

//         ListNode *ans = head->next;
//         head->next = head->next->next;
//         cur = head->next;
//         ListNode *newCur = ans;
//         while(cur){
//             newCur->next = cur->next;
//             cur->next = cur->next->next;
//             cur = cur->next;
//             newCur = newCur->next;
//         }

//         return ans;
//     }
// }

namespace PalindromeList{
    bool isPalindrome(ListNode *head){
        if(!head || !head->next)return true;

        ListNode *low = head, *fast = head;
        while(fast->next && fast->next->next){
            fast = fast->next->next;
            low = low->next;
        }

        ListNode *t = low;
        ListNode *next{};
        ListNode *pre{};
        while(t){
            next = t->next;
            t->next = pre;
            pre = t;
            t = next;
        }
        bool ans = true;
        ListNode *L = head, *R = pre;
        while(L && R){
            if(L->val != R->val){
                ans = false;
                break;
            }

            L = L->next;
            R = R->next;
        }

        t = pre;
        pre = nullptr;
        while(t){
            next = t->next;
            t->next = pre;
            pre = t;
            t = next;
        }

        return ans;
    }
}

namespace SortList{

    ListNode *start{}, *end{};

    ListNode *findEnd(ListNode *h, int step){
        while(--step != 0 && h->next){
            h = h->next;
        }

        return h;
    }

    void merge(ListNode *l1, ListNode *r1, ListNode *l2, ListNode *r2){
        r1->next = nullptr;
        r2->next = nullptr; 

        if(l1->val <= l2->val){
            start = l1;
            l1 = l1->next;
        }else{
            start = l2;
            l2 = l2->next;
        }
        end = start;
        while(l1 && l2){
            if(l1->val <= l2->val){
                end->next = l1;
                end = end->next;
                l1 = l1->next;
            }else{
                end->next = l2;
                end = end->next;
                l2 = l2->next;
            }
        }

        if(l1){
            end->next = l1;
            end = r1;
        }
        if(l2){
            end->next = l2;
            end = r2;
        }
    }

    ListNode* sortList(ListNode* head) {
        if (!head || !head->next)
            return head;

        int n{};
        ListNode* cur = head;
        while (cur) {
            n++;
            cur = cur->next;
        }
        ListNode *l1, *r1, *l2, *r2, *lastTeamEnd, *next;
        for (int step = 1; step < n; step <<= 1) {
            l1 = head;
            r1 = findEnd(l1, step);
            l2 = r1->next;
            r2 = findEnd(l2, step);
            next = r2->next;
            merge(l1, r1, l2, r2);
            head = start;
            lastTeamEnd = end;

            while (next) {
                l1 = next;
                r1 = findEnd(l1, step);
                l2 = r1->next;
                if(!l2){
                    lastTeamEnd->next = l1;
                    break;
                }
                r2 = findEnd(r2, step);
                next = r2->next;
                r1->next = nullptr;
                r2->next = nullptr;
                merge(l1, r1, l2, r2);
                lastTeamEnd->next = start;
                lastTeamEnd = end;
            }
        }

        return head;
    }
}

int main(){
    
}