//
// verify values stored locally are the same as the ones in the cloud
// cloud database is always regarded as source of truth
//
#define LOCAL_DATA
#define REMOTE_DATA
int verify_cloud_values(int OCCUPANCY, int CAPACITY, String SHELTER_CLASS,
                        int OCCUPANCY_REMOTE, int CAPACITY_REMOTE, String SHELTER_CLASS_REMOTE)
{
    enum LOCAL_DATA
    {
        OCCUPANCY,
        CAPACITY,
        SHELTER_CLASS
    };
    enum REMOTE_DATA
    {
        OCCUPANCY_REMOTE,
        CAPACITY_REMOTE,
        SHELTER_CLASS_REMOTE
    };

    for (int i = 0; i <= LOCAL_DATA.len(); i++)
    {
    }
}