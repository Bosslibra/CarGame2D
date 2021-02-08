#include <vector>
#include <string>
class LevelInterface
{

private:
    int height;
    int width;
    int level;
    int score;
    std::vector<std::vector<char>> canvas;
    /**
     * @brief inizializza il canvas (disegna i bordi)
     *
     */
    void initCanvas();

public:
    LevelInterface();
    ~LevelInterface();
    /**
     * @brief scrive lo score e il livello nel canvas
     *
     * @param level
     * @param score
     */
    void drawCanva(int level, int score);
    /**
     * @brief Get the Canvas object
     *
     * @return std::vector<std::vector<char>>
     */
    std::vector<std::vector<char>> getCanvas();
    /**
     * @brief Set the Height object
     *
     * @param height
     */
    void setHeight(int height);
};
