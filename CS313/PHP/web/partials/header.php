   <nav class="navbar fixed-top navbar-expand-lg navbar-light bg-light">
    <a class="navbar-brand" href="/">BYU-I ~ CS 313</a>
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
    </button>
    <div class="collapse navbar-collapse" id="navbarSupportedContent">
        <ul class="navbar-nav mr-auto">
            <li class="nav-item dropdown">
                <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                    Week 01
                </a>
                <div class="dropdown-menu" aria-labelledby="navbarDropdown">
                    <a class="dropdown-item" href="/hello.html">Hello, World!</a>
                </div>
            </li>
            <li class="nav-item dropdown">
                <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown2" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                    Week 02
                </a>
                <div class="dropdown-menu" aria-labelledby="navbarDropdown2">
                    <a class="dropdown-item" href="/w02/team/">Buttons and JavaScript</a>
                    <a class="dropdown-item" href="/index.php">Home Page</a>
                </div>
            </li>
            <li class="nav-item dropdown">
                <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown3" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                    Week 03
                </a>
                <div class="dropdown-menu" aria-labelledby="navbarDropdown3">
                    <a class="dropdown-item" href="/w03/team/">PHP Form Handling</a>
                    <a class="dropdown-item" href="/w03/prove/">Pok&#233; Shop</a>
                </div>
            </li>
            <li class="nav-item dropdown">
                <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown4" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                    Week 04
                </a>
                <div class="dropdown-menu" aria-labelledby="navbarDropdown4">
                    <a class="dropdown-item" href="/w04/">Week 4 Download Page</a>
                </div>
            </li>
            <li class="nav-item dropdown">
                <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown5" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                    Week 05
                </a>
                <div class="dropdown-menu" aria-labelledby="navbarDropdown5">
                    <a class="dropdown-item" href="/w05/team/">Display Query Results</a>
                    <a class="dropdown-item" href="/proj/v1/">Read Only Task Killer</a>
                </div>
            </li>
            <li class="nav-item dropdown">
                <a class="nav-link dropdown-toggle" href="#" id="navbarDropdown6" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                    Week 06
                </a>
                <div class="dropdown-menu" aria-labelledby="navbarDropdown6">
                    <a class="dropdown-item" href="/w06/team/">Scripture Resource Add</a>
                    <a class="dropdown-item" href="/proj/v2/">Complete Task Killer</a>
                </div>
            </li>
        </ul>
        <ul class="navbar-nav">
            <?php if(!isset($_SESSION['valid'])) {?>   
                <li class="nav-item">
                    <a href="/signup.php" class="nav-link">Sign Up</a>
                </li>
                <li class="nav-item">
                    <a href="/login.php" class="nav-link">Login</a>

                </li>
            <?php } else {?>
                <li class="nav-item">
                    <a href="/logout.php" class="nav-link">logout</a>
                </li>
            <?php } ?>     
        </ul>

    </div>
</nav>
