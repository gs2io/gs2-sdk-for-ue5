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

namespace Gs2::Deploy::Model
{
    class GS2DEPLOY_API FOutput final : public FGs2Object, public TSharedFromThis<FOutput>
    {
        TOptional<FString> OutputIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> ValueValue;
        TOptional<int64> CreatedAtValue;

    public:
        FOutput();
        FOutput(
            const FOutput& From
        );
        virtual ~FOutput() override = default;

        TSharedPtr<FOutput> WithOutputId(const TOptional<FString> OutputId);
        TSharedPtr<FOutput> WithName(const TOptional<FString> Name);
        TSharedPtr<FOutput> WithValue(const TOptional<FString> Value);
        TSharedPtr<FOutput> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetOutputId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetValue() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetStackNameFromGrn(const FString Grn);
        static TOptional<FString> GetOutputNameFromGrn(const FString Grn);

        static TSharedPtr<FOutput> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FOutput, ESPMode::ThreadSafe> FOutputPtr;
}