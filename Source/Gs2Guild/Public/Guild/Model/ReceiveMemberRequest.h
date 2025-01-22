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
    class GS2GUILD_API FReceiveMemberRequest final : public Gs2Object, public TSharedFromThis<FReceiveMemberRequest>
    {
        TOptional<FString> UserIdValue;
        TOptional<FString> TargetGuildNameValue;
        TOptional<FString> MetadataValue;

    public:
        FReceiveMemberRequest();
        FReceiveMemberRequest(
            const FReceiveMemberRequest& From
        );
        virtual ~FReceiveMemberRequest() override = default;

        TSharedPtr<FReceiveMemberRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FReceiveMemberRequest> WithTargetGuildName(const TOptional<FString> TargetGuildName);
        TSharedPtr<FReceiveMemberRequest> WithMetadata(const TOptional<FString> Metadata);

        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTargetGuildName() const;
        TOptional<FString> GetMetadata() const;


        static TSharedPtr<FReceiveMemberRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FReceiveMemberRequest, ESPMode::ThreadSafe> FReceiveMemberRequestPtr;
}