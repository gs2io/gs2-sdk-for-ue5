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
    class FSetMoldCapacityByUserIdRequest;

    class GS2FORMATION_API FSetMoldCapacityByUserIdRequest final : public TSharedFromThis<FSetMoldCapacityByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MoldModelNameValue;
        TOptional<int32> CapacityValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FSetMoldCapacityByUserIdRequest();
        FSetMoldCapacityByUserIdRequest(
            const FSetMoldCapacityByUserIdRequest& From
        );
        ~FSetMoldCapacityByUserIdRequest() = default;

        TSharedPtr<FSetMoldCapacityByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FSetMoldCapacityByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSetMoldCapacityByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FSetMoldCapacityByUserIdRequest> WithMoldModelName(const TOptional<FString> MoldModelName);
        TSharedPtr<FSetMoldCapacityByUserIdRequest> WithCapacity(const TOptional<int32> Capacity);
        TSharedPtr<FSetMoldCapacityByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMoldModelName() const;
        TOptional<int32> GetCapacity() const;
        FString GetCapacityString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FSetMoldCapacityByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetMoldCapacityByUserIdRequest, ESPMode::ThreadSafe> FSetMoldCapacityByUserIdRequestPtr;
}