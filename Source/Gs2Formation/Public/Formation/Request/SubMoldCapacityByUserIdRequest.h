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

namespace Gs2::Formation::Request
{
    class FSubMoldCapacityByUserIdRequest;

    class GS2FORMATION_API FSubMoldCapacityByUserIdRequest final : public TSharedFromThis<FSubMoldCapacityByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MoldModelNameValue;
        TOptional<int32> CapacityValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSubMoldCapacityByUserIdRequest();
        FSubMoldCapacityByUserIdRequest(
            const FSubMoldCapacityByUserIdRequest& From
        );
        ~FSubMoldCapacityByUserIdRequest() = default;

        TSharedPtr<FSubMoldCapacityByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSubMoldCapacityByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSubMoldCapacityByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSubMoldCapacityByUserIdRequest> WithMoldModelName(const TOptional<FString> MoldModelName);
        TSharedPtr<FSubMoldCapacityByUserIdRequest> WithCapacity(const TOptional<int32> Capacity);
        TSharedPtr<FSubMoldCapacityByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FSubMoldCapacityByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMoldModelName() const;
        TOptional<int32> GetCapacity() const;
        FString GetCapacityString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSubMoldCapacityByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSubMoldCapacityByUserIdRequest, ESPMode::ThreadSafe> FSubMoldCapacityByUserIdRequestPtr;
}