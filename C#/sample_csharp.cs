// Visual sample for C#.sublime-syntax — open in Sublime and eyeball the colors.
/// <summary>XML doc comment with a <c>tag</c>.</summary>
/* block comment with an apostrophe ' and a quote " that must NOT run away */

#region Usings
using System;
using System.Collections.Generic;
using static System.Math;
using Json = System.Text.Json;
global using System.Linq;
#endregion

namespace Demo.App;

[Serializable]
public abstract class Widget<T> : BaseWidget, IDisposable where T : class
{
    public const double Ratio = 1.618;
    private static readonly int[] Primes = { 2, 3, 5, 7, 11 };
    public string Name { get; set; } = "unnamed";

    // numbers: hex, binary, float, separators, suffixes
    private long mask = 0xDEAD_BEEFL;
    private int flags = 0b1010_0101;
    private decimal price = 19.99m;
    private double sci = 6.022e23;

    public Widget(string name) : base(name)
    {
        Name = name;
        var verbatim = @"C:\temp\no\escapes "" here";
        var interp = $"Hello {name}, ratio={Ratio:F2}!";
        var raw = """
            raw "string" literal, no escaping needed
            """;
        char c = '\n';
    }

    public async Task<int> ComputeAsync(int x, int y = Add(1, 2))
    {
        if (x > y && y != 0)
            return await Task.FromResult(x % y);
        foreach (var p in Primes)
            Console.WriteLine($"prime: {p}");
        return checked(x + y);
    }

    private static int Add(int a, int b) => a + b;
}

public enum Level : byte { Low, Medium = 5, High = Low | Medium }

public record struct Point(int X, int Y);
