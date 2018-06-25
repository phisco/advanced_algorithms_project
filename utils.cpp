
template <class Result1, class Result2>
bool compare_results(const Result1 r1, const Result2 r2){
    if (r1.size() != r2.size())
        return false;
    int maxVal=0;
    for(int i=0; i!=r1.size(); i++){
        maxVal = std::max(maxVal, r1[i]);
    }
    for(int i=0; i!=r2.size(); i++){
        maxVal = std::max(maxVal, r2[i]);
    }
    int comp[maxVal+1];
    for (int i=0; i != maxVal+1; i++)
        comp[i]=0;

    for (int i = 0; i != r1.size(); i++){
        if (comp[r1[i]]==0)
            comp[r1[i]]=r2[i];
        if (comp[r1[i]]!=r2[i]){
            return false;
        }
    }
    return true;
}