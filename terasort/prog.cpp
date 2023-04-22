#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <parallel/algorithm>

using namespace std;

// Chunk size in bytes
const int CHUNK_SIZE = 1 * 1024 * 1024; // 1 MB

// Key-value pair struct
struct KeyValue
{
    int key;
    string value;
};

// Read the next chunk from file
vector<KeyValue> readChunk(ifstream &inputFile)
{
    vector<KeyValue> chunk;
    chunk.reserve(CHUNK_SIZE / sizeof(KeyValue));
    KeyValue kv;
    string line;
    int bytesRead = 0;
    while (getline(inputFile, line))
    {
        bytesRead += line.size() + 1; // include newline character
        sscanf(line.c_str(), "%d", &kv.key);
        kv.value = line.substr(line.find(' ') + 1);
        chunk.push_back(kv);
        if (bytesRead >= CHUNK_SIZE)
        {
            return chunk;
        }
    }
    return chunk;
}

// Write the chunk to file
void writeChunk(ofstream &outputFile, const vector<KeyValue> &chunk)
{
    for (const auto &kv : chunk)
    {
        outputFile << kv.key << " " << kv.value << endl;
    }
}

// Merge the sorted chunks
void mergeChunks(const vector<string> &chunkFiles, const string &outputFilename)
{
    vector<ifstream> chunkStreams(chunkFiles.size());
    for (size_t i = 0; i < chunkFiles.size(); ++i)
    {
        chunkStreams[i].open(chunkFiles[i], ios::binary);
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<KeyValue> kvBuffer(chunkFiles.size());
    for (size_t i = 0; i < chunkStreams.size(); ++i)
    {
        if (chunkStreams[i] >> kvBuffer[i].key)
        {
            getline(chunkStreams[i], kvBuffer[i].value);
            pq.push({kvBuffer[i].key, i});
        }
    }
    ofstream outputFile(outputFilename, ios::binary);
    while (!pq.empty())
    {
        int i = pq.top().second;
        pq.pop();
        outputFile << kvBuffer[i].key << " " << kvBuffer[i].value << endl;
        if (chunkStreams[i] >> kvBuffer[i].key)
        {
            getline(chunkStreams[i], kvBuffer[i].value);
            pq.push({kvBuffer[i].key, i});
        }
    }
    for (auto &stream : chunkStreams)
    {
        stream.close();
    }
    outputFile.close();
}

// Sort the input file
// Sort the input file
void sortFile(const string &inputFilename, const string &outputFilename)
{
    // Sort the input file
    vector<string> chunkFiles;
    ifstream input(inputFilename);
    int chunkNum = 0;

    for (int i = 0; !input.eof(); ++i)
    {
        auto chunk = readChunk(input);
        if (chunk.empty())
        {
            break;
        }
        __gnu_parallel::sort(chunk.begin(), chunk.end(), [](const auto &kv1, const auto &kv2)
             { return kv1.value < kv2.value; });

        string chunkFilename = "chunk_" + to_string(i) + ".txt";
        ofstream chunkFile(chunkFilename);
        writeChunk(chunkFile, chunk);
        chunkFiles.push_back(chunkFilename);
    }
    input.close();
    mergeChunks(chunkFiles, outputFilename);
    for (const auto &filename : chunkFiles)
    {
        remove(filename.c_str());
    }
}

// Test the implementation
int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cout << "Usage: " << argv[0] << " input-file output-file" << endl;
        return 1;
    }
    sortFile(argv[1], argv[2]);
    return 0;
}
