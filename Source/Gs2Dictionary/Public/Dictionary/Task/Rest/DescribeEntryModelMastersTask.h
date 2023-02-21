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

#include "Core/Gs2Core.h"
#include "Dictionary/Request/DescribeEntryModelMastersRequest.h"
#include "Dictionary/Result/DescribeEntryModelMastersResult.h"

namespace Gs2::Dictionary::Task::Rest
{
    class GS2DICTIONARY_API FDescribeEntryModelMastersTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeEntryModelMastersResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FDescribeEntryModelMastersRequestPtr Request;
    public:
        explicit FDescribeEntryModelMastersTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FDescribeEntryModelMastersRequestPtr Request
        );
        FDescribeEntryModelMastersTask(
            const FDescribeEntryModelMastersTask& From
        );
        virtual ~FDescribeEntryModelMastersTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeEntryModelMastersResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeEntryModelMastersTask, ESPMode::ThreadSafe> FDescribeEntryModelMastersTaskPtr;
}