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

namespace Gs2::Account::Model
{
    class GS2ACCOUNT_API FPlatformUser final : public Gs2Object, public TSharedFromThis<FPlatformUser>
    {
        TOptional<int32> TypeValue;
        TOptional<FString> UserIdentifierValue;
        TOptional<FString> UserIdValue;

    public:
        FPlatformUser();
        FPlatformUser(
            const FPlatformUser& From
        );
        virtual ~FPlatformUser() override = default;

        TSharedPtr<FPlatformUser> WithType(const TOptional<int32> Type);
        TSharedPtr<FPlatformUser> WithUserIdentifier(const TOptional<FString> UserIdentifier);
        TSharedPtr<FPlatformUser> WithUserId(const TOptional<FString> UserId);

        TOptional<int32> GetType() const;
        FString GetTypeString() const;
        TOptional<FString> GetUserIdentifier() const;
        TOptional<FString> GetUserId() const;


        static TSharedPtr<FPlatformUser> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FPlatformUser, ESPMode::ThreadSafe> FPlatformUserPtr;
}