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
    class GS2DISTRIBUTOR_API FBatchResultPayload final : public FGs2Object, public TSharedFromThis<FBatchResultPayload>
    {
        TOptional<FString> RequestIdValue;
        TOptional<int32> StatusCodeValue;
        TOptional<FString> ResultPayloadValue;

    public:
        FBatchResultPayload();
        FBatchResultPayload(
            const FBatchResultPayload& From
        );
        virtual ~FBatchResultPayload() override = default;

        TSharedPtr<FBatchResultPayload> WithRequestId(const TOptional<FString> RequestId);
        TSharedPtr<FBatchResultPayload> WithStatusCode(const TOptional<int32> StatusCode);
        TSharedPtr<FBatchResultPayload> WithResultPayload(const TOptional<FString> ResultPayload);

        TOptional<FString> GetRequestId() const;
        TOptional<int32> GetStatusCode() const;
        FString GetStatusCodeString() const;
        TOptional<FString> GetResultPayload() const;


        static TSharedPtr<FBatchResultPayload> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBatchResultPayload, ESPMode::ThreadSafe> FBatchResultPayloadPtr;
}