/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:05:56 by spoolpra          #+#    #+#             */
/*   Updated: 2022/08/27 16:51:46 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SLOWRUNTIME 10
#define GOODRUNTIME 0

#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <fcntl.h>

typedef struct info
{
    int     status;
    timeval runtime;
} info;

info test_file(const std::string& path);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./tester [std_file] [ft_file]" << std::endl;
        return (0);
    }
    info std_info = test_file(argv[1]);
    info ft_info = test_file(argv[2]);
    if (ft_info.status != 0)
    {
        return (ft_info.status);
    }
    time_t ft_runtime = (ft_info.runtime.tv_sec * 1000000) + ft_info.runtime.tv_usec;
    time_t std_runtime = (std_info.runtime.tv_sec * 1000000) + std_info.runtime.tv_usec;
    if (ft_runtime / std_runtime >= 20)
    {
        return (SLOWRUNTIME);
    }
    return (GOODRUNTIME);
}

std::string find_log_name(const std::string& path)
{
    std::string test_name;
    std::string dir_name;
    const size_t last_slash_idx = path.rfind('/');
    if (std::string::npos != last_slash_idx)
    {
        dir_name = path.substr(0, last_slash_idx);
        test_name = path.substr(last_slash_idx);
    }
    std::string log_path(dir_name + "/logs" + test_name + ".log");
    return log_path;
}

info test_file(const std::string& path)
{
    std::string log_path = find_log_name(path);
    int fd = open(log_path.c_str(), O_CREAT | O_WRONLY, 0644);
    char* const argv[2] = {const_cast<char *>(path.c_str()), NULL};
    pid_t pid = fork();

    /// Fork failed
    if (pid < -1)
    {
        exit(3);
    }
    /// Child Process execute test file
    if (pid == 0)
    {
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);
        execv(path.c_str(), argv);
        exit(3);
    }
    /// Parent Process time child process runtime and wait for any exit status error
    else
    {
        info ret;
        int status;
        timeval before;
        gettimeofday(&before, NULL);
        if (waitpid(pid, &status, 0) == -1)
        {
            exit(3);
        }
        timeval after;
        gettimeofday(&after, NULL);
        ret.status = status;
        timersub(&after, &before, &ret.runtime);
        return ret;
    }
}
