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
#include "SkillTree/Request/GetNamespaceRequest.h"
#include "SkillTree/Result/GetNamespaceResult.h"

namespace Gs2::SkillTree::Task::Rest
{
    class GS2SKILLTREE_API FGetNamespaceTask final : public Gs2::Core::Util::TGs2Future<Result::FGetNamespaceResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FGetNamespaceRequestPtr Request;
    public:
        explicit FGetNamespaceTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FGetNamespaceRequestPtr Request
        );
        FGetNamespaceTask(
            const FGetNamespaceTask& From
        );
        virtual ~FGetNamespaceTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FGetNamespaceResultPtr> Result) override;
    };
    typedef TSharedPtr<FGetNamespaceTask, ESPMode::ThreadSafe> FGetNamespaceTaskPtr;
}