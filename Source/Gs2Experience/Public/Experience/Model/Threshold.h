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

namespace Gs2::Experience::Model
{
    class GS2EXPERIENCE_API FThreshold final : public FGs2Object, public TSharedFromThis<FThreshold>
    {
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<int64>> ValuesValue;

    public:
        FThreshold();
        FThreshold(
            const FThreshold& From
        );
        virtual ~FThreshold() override = default;

        TSharedPtr<FThreshold> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FThreshold> WithValues(const TSharedPtr<TArray<int64>> Values);

        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<int64>> GetValues() const;


        static TSharedPtr<FThreshold> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FThreshold, ESPMode::ThreadSafe> FThresholdPtr;
}