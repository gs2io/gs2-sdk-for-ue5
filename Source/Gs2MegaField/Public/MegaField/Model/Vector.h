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

namespace Gs2::MegaField::Model
{
    class GS2MEGAFIELD_API FVector final : public Gs2Object, public TSharedFromThis<FVector>
    {
        TOptional<float> XValue;
        TOptional<float> YValue;
        TOptional<float> ZValue;

    public:
        FVector();
        FVector(
            const FVector& From
        );
        virtual ~FVector() override = default;

        TSharedPtr<FVector> WithX(const TOptional<float> X);
        TSharedPtr<FVector> WithY(const TOptional<float> Y);
        TSharedPtr<FVector> WithZ(const TOptional<float> Z);

        TOptional<float> GetX() const;
        FString GetXString() const;
        TOptional<float> GetY() const;
        FString GetYString() const;
        TOptional<float> GetZ() const;
        FString GetZString() const;


        static TSharedPtr<FVector> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FVector, ESPMode::ThreadSafe> FVectorPtr;
}