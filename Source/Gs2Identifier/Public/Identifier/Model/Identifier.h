/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "Core/Gs2Object.h"

namespace Gs2::Identifier::Model
{
    class GS2IDENTIFIER_API FIdentifier final : public Gs2Object, public TSharedFromThis<FIdentifier>
    {
        TOptional<FString> ClientIdValue;
        TOptional<FString> UserNameValue;
        TOptional<FString> ClientSecretValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FIdentifier();
        FIdentifier(
            const FIdentifier& From
        );
        virtual ~FIdentifier() override = default;

        TSharedPtr<FIdentifier> WithClientId(const TOptional<FString> ClientId);
        TSharedPtr<FIdentifier> WithUserName(const TOptional<FString> UserName);
        TSharedPtr<FIdentifier> WithClientSecret(const TOptional<FString> ClientSecret);
        TSharedPtr<FIdentifier> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FIdentifier> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetClientId() const;
        TOptional<FString> GetUserName() const;
        TOptional<FString> GetClientSecret() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;


        static TSharedPtr<FIdentifier> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FIdentifier, ESPMode::ThreadSafe> FIdentifierPtr;
}