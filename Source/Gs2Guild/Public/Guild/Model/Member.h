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

namespace Gs2::Guild::Model
{
    class GS2GUILD_API FMember final : public Gs2Object, public TSharedFromThis<FMember>
    {
        TOptional<FString> UserIdValue;
        TOptional<FString> RoleNameValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> JoinedAtValue;

    public:
        FMember();
        FMember(
            const FMember& From
        );
        virtual ~FMember() override = default;

        TSharedPtr<FMember> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FMember> WithRoleName(const TOptional<FString> RoleName);
        TSharedPtr<FMember> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FMember> WithJoinedAt(const TOptional<int64> JoinedAt);

        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRoleName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetJoinedAt() const;
        FString GetJoinedAtString() const;


        static TSharedPtr<FMember> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FMember, ESPMode::ThreadSafe> FMemberPtr;
}