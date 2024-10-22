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
#include "Dom/JsonObject.h"
#include "../Model/Config.h"

namespace Gs2::Quest::Request
{
    class FStartByUserIdRequest;

    class GS2QUEST_API FStartByUserIdRequest final : public TSharedFromThis<FStartByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> QuestGroupNameValue;
        TOptional<FString> QuestNameValue;
        TOptional<FString> UserIdValue;
        TOptional<bool> ForceValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FStartByUserIdRequest();
        FStartByUserIdRequest(
            const FStartByUserIdRequest& From
        );
        ~FStartByUserIdRequest() = default;

        TSharedPtr<FStartByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FStartByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FStartByUserIdRequest> WithQuestGroupName(const TOptional<FString> QuestGroupName);
        TSharedPtr<FStartByUserIdRequest> WithQuestName(const TOptional<FString> QuestName);
        TSharedPtr<FStartByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FStartByUserIdRequest> WithForce(const TOptional<bool> Force);
        TSharedPtr<FStartByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FStartByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FStartByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetQuestGroupName() const;
        TOptional<FString> GetQuestName() const;
        TOptional<FString> GetUserId() const;
        TOptional<bool> GetForce() const;
        FString GetForceString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FStartByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FStartByUserIdRequest> FStartByUserIdRequestPtr;
}