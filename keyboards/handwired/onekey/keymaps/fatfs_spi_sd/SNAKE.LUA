-------------
-- Game state
MAX_X    = 16
MAX_Y    = 16

-- TILES
AIR        = 0
SNAKE_HEAD = 1
SNAKE_BODY = 2
SNAKE_TAIL = 3
FOOD       = 4
WALL       = 5

-------
-- Food
local function random_food_pos()
    return math.random(MAX_X), math.random(MAX_Y)
end

local function create_food(game)
    local x, y = random_food_pos()

    -- no food at tiles with stuff
    while game[y][x] ~= AIR do
        x, y = random_food_pos()
    end

    game[y][x] = FOOD
end

local function check_food(game, head)
    -- after eating, create new food
    if game[head.y][head.x] == FOOD then
        create_food(game)
        return true
    end

    return false
end

-----------------------
-- Create playing field
local function init_game()
    local args = {
        ["game"]          = {},
        ["old_game"]      = {},
        ["direction"]     = "d",
        ["old_direction"] = "__stop__"
    }

    local function new_row(r)
        local row = {}
        for c = 1, MAX_X do
            if
                r == 1
                or r == MAX_Y
                or c == 1
                or c == MAX_X
            then
                row[c] = WALL
            else
                row[c] = AIR
            end
        end

        return row
    end

    for r = 1, MAX_Y do
        args["game"][r]     = new_row(r)
        args["old_game"][r] = {}
    end

    args["snake"] = {{x = MAX_X//2, y = MAX_Y//2}}

    local head = args["snake"][1]
    args["game"][head.y][head.x] = SNAKE_HEAD

    create_food(args["game"])

    return args
end

local function snapshot(args)
    for r, row in pairs(args["game"]) do
        args["old_game"][r] = {} -- empty table
        for c, col in pairs(row) do
            args["old_game"][r][c] = col
        end
    end
end

-------------
-- Game logic
local function delta(direction)
    local map = {
        ["W"]        = { 0, -1},
        ["w"]        = { 0, -1},
        ["A"]        = {-1,  0},
        ["a"]        = {-1,  0},
        ["S"]        = { 0,  1},
        ["s"]        = { 0,  1},
        ["D"]        = { 1,  0},
        ["d"]        = { 1,  0},
        ["__stop__"] = { 0,  0},
    }

    local value = map[direction]

    if value == nil then
        print("INVALID INPUT")
        os.exit()
    end

    return table.unpack(value)
end

local function snake_move(args)
    local game = args["game"]
    local snake = args["snake"]
    local old_direction = args["old_direction"]

    local old_head = snake[1]

    local delta_x, delta_y = delta(old_direction)
    local new_head = {x = old_head.x + delta_x, y = old_head.y + delta_y}

    -- BODY/WALL --------------------------------
    local target_tile = game[new_head.y][new_head.x]
    if
        target_tile == SNAKE_HEAD -- not possible (?)
        or target_tile == SNAKE_TAIL
        or target_tile == SNAKE_BODY
        or target_tile == WALL
    then
        return false
    end
    ---------------------------------------------

    -- FOOD -------------------------------------
    local eaten = check_food(game, new_head)

    -- new head at start of our "queue"
    table.insert(snake, 1, new_head)
    game[new_head.y][new_head.x] = SNAKE_HEAD

    -- old head is now body
    game[old_head.y][old_head.x] = SNAKE_BODY

    -- eaten: nothing to be done

    if not eaten then
        -- remove tail
        local old_tail = table.remove(snake)
        game[old_tail.y][old_tail.x] = AIR

        -- last element is now tail, unless we have a single body part (head)
        local size = #snake
        if size > 1 then
            local new_tail = snake[size]
            game[new_tail.y][new_tail.x] = SNAKE_TAIL
        end
    end

    return true
end
---------------------------------------------

local function validate_move(direction, snake)
    -- Check if user input would be a valid move
    local head, neck = snake[1], snake[2]

    -- First iteration, no neck, can move anywhere
    if neck == nil then
        return true
    end

    local delta_x, delta_y = delta(direction)

    if head.x + delta_x == neck.x and head.y + delta_y == neck.y then
        return false
    end

    return true
end

-----------
-- Graphics
local function render_tile(args, row, col)
    local device_id = 0

    local tile     = args["game"][row][col]
    local old_tile = args["old_game"][row][col]

    if tile == old_tile then
        return
    end

    local map = {
        [AIR]        = HSV_BLACK,
        [FOOD]       = HSV_RED,
        [SNAKE_HEAD] = HSV_YELLOW,
        [SNAKE_BODY] = HSV_GREEN,
        [SNAKE_TAIL] = HSV_BLUE,
        [WALL]       = HSV_WHITE,
    }
    local color = map[tile]

    qp_rect(
        device_id,
        row * 15,
        col * 15,
        (row + 1) * 15,
        (col + 1) * 15,
        color,
        true
    )
end

local function render_game(args)
    for row = 1, MAX_Y do
        for col = 1, MAX_X do
            render_tile(args, row, col)
        end
        io.write("\n")
    end
end

-----------
-- Mainloop
local function mainloop(args)
    -- Create/override values
    if args == nil then
        args = init_game()
    end

    local snake         = args["snake"]
    local direction     = args["direction"]

    -- user input
    if
        direction == "\n"
        or direction == ""
    then
        direction = nil
    end

    -- TODO: Input to quit
    -- If user inputs but it would move to the snake's head
    --   > Not valid, ignore input and move in current direction
    if direction ~= nil and validate_move(direction, snake) then
        args["old_direction"] = direction
    end

    -- snapshot current map, reduce redraws
    snapshot(args)

    -- this updates game
    local alive = snake_move(args)

    -- draws by comparing game with old_game
    render_game(args)

    args["alive"] = alive

    return args
end

return mainloop
