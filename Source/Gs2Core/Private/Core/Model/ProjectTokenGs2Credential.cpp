/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 */

#include "Core/Model/ProjectTokenGs2Credential.h"

namespace Gs2::Core::Model
{
    FProjectTokenGs2Credential::FProjectTokenGs2Credential(
        FString ClientId,
        FString ProjectToken
    ):
        ClientIdValue(ClientId),
        ClientSecretValue(""),
        ProjectTokenValue(ProjectToken)
    {
    }

    const FGs2ClientId& FProjectTokenGs2Credential::ClientId() const
    {
        return ClientIdValue;
    }

    const FGs2ClientSecret& FProjectTokenGs2Credential::ClientSecret() const
    {
        return ClientSecretValue;
    }

    const FGs2ProjectToken& FProjectTokenGs2Credential::ProjectToken() const
    {
        return ProjectTokenValue;
    }

    void FProjectTokenGs2Credential::UpdateProjectToken(const FGs2ProjectToken& Token)
    {
        ProjectTokenValue = Token;
    }
}
