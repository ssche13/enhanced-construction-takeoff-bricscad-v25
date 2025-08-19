# Security Policy

## Supported Versions

We provide security updates for the following versions of Enhanced Construction Takeoff:

| Version | Supported          |
| ------- | ------------------ |
| 1.0.x   | :white_check_mark: |
| < 1.0   | :x:                |

## Reporting a Vulnerability

We take the security of Enhanced Construction Takeoff seriously. If you believe you have found a security vulnerability, please report it to us as described below.

### How to Report a Security Vulnerability

**Please do not report security vulnerabilities through public GitHub issues.**

Instead, please report them via email to: [security@yourproject.com] or create a private security advisory on GitHub.

### What to Include in Your Report

Please include the following information in your report:

- **Type of issue**: (e.g., buffer overflow, privilege escalation, information disclosure)
- **Full paths of source file(s)** related to the manifestation of the issue
- **The location of the affected source code** (tag/branch/commit or direct URL)
- **Any special configuration required** to reproduce the issue
- **Step-by-step instructions to reproduce the issue**
- **Proof-of-concept or exploit code** (if possible)
- **Impact of the issue**, including how an attacker might exploit it

### Response Timeline

We will acknowledge your email within 48 hours and will send a more detailed response within 72 hours indicating the next steps in handling your report.

After the initial reply to your report, we will endeavor to keep you informed of the progress being made towards a fix and full announcement.

## Security Considerations

### BricsCAD Integration

This plugin integrates with BricsCAD V25 and has access to:
- Drawing database
- File system (for Excel integration)
- Windows COM interfaces (for Excel)
- User-defined material assignments

### Data Handling

- **Material Assignments**: Stored locally, not transmitted
- **Excel Integration**: Uses local COM interfaces only
- **Drawing Data**: Accessed read-only for quantity calculations
- **User Preferences**: Stored in local registry/config files

### Known Limitations

- Requires BricsCAD V25 with BRX SDK
- Windows-only implementation
- Depends on Microsoft Office Excel for Excel integration
- Requires elevated permissions for plugin installation

### Best Practices for Users

1. **Plugin Source**: Only install from official releases
2. **Permissions**: Review file system access requirements
3. **Excel Files**: Backup Excel files before integration
4. **Updates**: Keep plugin updated to latest version

## Threat Model

### Assets Protected
- User drawing data
- Material assignment configurations
- Excel workbook formulas and data
- System integrity

### Potential Threats
- Malicious drawing files
- Excel macro execution
- File system access abuse
- Memory corruption vulnerabilities

### Mitigations Implemented
- Input validation for all user data
- Proper error handling and resource cleanup
- Read-only access to drawing database where possible
- No automatic macro execution in Excel files

## Dependencies Security

### BricsCAD BRX SDK
- Commercial SDK with security support
- Regular updates from Bricsys
- Proper API usage with transaction handling

### Microsoft Visual C++ Runtime
- Standard Microsoft runtime libraries
- Updated through Windows Update
- Industry-standard security practices

### Windows COM
- Standard Windows component
- Used only for Excel integration
- No custom COM components

## Disclosure Policy

When we receive a security bug report, we will:

1. **Confirm the problem** and determine affected versions
2. **Audit code** to find any potential similar problems
3. **Prepare fixes** for all supported releases
4. **Release new versions** as soon as possible
5. **Announce the vulnerability** in our security advisories

## Comments on This Policy

If you have suggestions on how this process could be improved, please submit a pull request or file an issue to discuss.

---

**Last Updated**: December 19, 2024  
**Version**: 1.0