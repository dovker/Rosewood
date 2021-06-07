//Import
//ImportPacked
//
/*

struct AssetMetaData
{
    Path,
    Name,
    Type,
    ...

}

*/
/*
Class is static, therefore you need to deserialize to gain data

How do I do references with them being different types??

Maybe put it all into Assets class
And then add Export function
Maybe just keep MetaData vector and add to it whenever you please and then export metadata instead of assets
Ching ching!!


ImportPacked
{
    name = ZipGetCurrentFilename
    metadata = deserialize(Yaml::find(name))
    std::vector<byte> file;


}

ImportRaw(vector file, metadata meta)
{
    switch(meta.type)
    {

    }
}

*/