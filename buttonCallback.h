int buttonCallback(int id) {
    int value = id; // Example value - could be from user input
    
    switch(value) {
        case 1:
            printf("Case 1\n");
            break;
        case 2:
            printf("Case 2\n");
            break;
        case 3:
            printf("Case 3\n");
            break;
        case 4:
            printf("Case 100\n");
            break;
        default:
            printf("default");
            break;
    }
    
    return 0;
}
