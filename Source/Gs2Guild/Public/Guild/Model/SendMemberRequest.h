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
    class GS2GUILD_API FSendMemberRequest final : public FGs2Object, public TSharedFromThis<FSendMemberRequest>
    {
        TOptional<FString> UserIdValue;
        TOptional<FString> TargetGuildNameValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> CreatedAtValue;

    public:
        FSendMemberRequest();
        FSendMemberRequest(
            const FSendMemberRequest& From
        );
        virtual ~FSendMemberRequest() override = default;

        TSharedPtr<FSendMemberRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSendMemberRequest> WithTargetGuildName(const TOptional<FString> TargetGuildName);
        TSharedPtr<FSendMemberRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSendMemberRequest> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTargetGuildName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;


        static TSharedPtr<FSendMemberRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSendMemberRequest, ESPMode::ThreadSafe> FSendMemberRequestPtr;
}