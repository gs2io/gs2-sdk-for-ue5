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

namespace Gs2::Distributor::Model
{
    class GS2DISTRIBUTOR_API FBatchRequestPayload final : public Gs2Object, public TSharedFromThis<FBatchRequestPayload>
    {
        TOptional<FString> RequestIdValue;
        TOptional<FString> ServiceValue;
        TOptional<FString> MethodNameValue;
        TOptional<FString> ParameterValue;

    public:
        FBatchRequestPayload();
        FBatchRequestPayload(
            const FBatchRequestPayload& From
        );
        virtual ~FBatchRequestPayload() override = default;

        TSharedPtr<FBatchRequestPayload> WithRequestId(const TOptional<FString> RequestId);
        TSharedPtr<FBatchRequestPayload> WithService(const TOptional<FString> Service);
        TSharedPtr<FBatchRequestPayload> WithMethodName(const TOptional<FString> MethodName);
        TSharedPtr<FBatchRequestPayload> WithParameter(const TOptional<FString> Parameter);

        TOptional<FString> GetRequestId() const;
        TOptional<FString> GetService() const;
        TOptional<FString> GetMethodName() const;
        TOptional<FString> GetParameter() const;


        static TSharedPtr<FBatchRequestPayload> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBatchRequestPayload, ESPMode::ThreadSafe> FBatchRequestPayloadPtr;
}