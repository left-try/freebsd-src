local acpi = {}

-- Simulated list of ACPI table signatures.
function acpi.list_tables()
    return { "DSDT", "FACP", "SSDT1", "SSDT2" }
end

-- Simulated ACPI table data.
local table_data = {
    DSDT  = "Simulated DSDT table contents ...",
    FACP  = "Simulated FACP table contents ...",
    SSDT1 = "Simulated SSDT1 table contents ...",
    SSDT2 = "Simulated SSDT2 table contents ..."
}

-- Returns the content of a specified ACPI table.
function acpi.get_table(signature)
    return table_data[signature]
end

-- Simulated evaluation of an ACPI method.
function acpi.evaluate_method(method, args)
    -- For testing, simply return a string that shows what method was "called".
    return "Simulated result for method: " .. method
end

return acpi
