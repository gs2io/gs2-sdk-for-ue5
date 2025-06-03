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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Freeze/Domain/Gs2Freeze.h"
#include "Freeze/Domain/Model/Stage.h"
#include "Freeze/Domain/Model/Output.h"
#include "Core/Domain/Gs2.h"

namespace Gs2::Freeze::Domain
{

    FGs2FreezeDomain::FGs2FreezeDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Freeze::FGs2FreezeRestClient>(Gs2->RestSession)),
        ParentKey("freeze")
    {
    }

    FGs2FreezeDomain::FGs2FreezeDomain(
        const FGs2FreezeDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Freeze::Domain::Iterator::FDescribeStagesIteratorPtr FGs2FreezeDomain::Stages(
    ) const
    {
        return MakeShared<Gs2::Freeze::Domain::Iterator::FDescribeStagesIterator>(
            Gs2,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2FreezeDomain::SubscribeStages(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Freeze::Model::FStage::TypeName,
            "freeze:Stage",
            Callback
        );
    }

    void FGs2FreezeDomain::UnsubscribeStages(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Freeze::Model::FStage::TypeName,
            "freeze:Stage",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Freeze::Domain::Model::FStageDomain> FGs2FreezeDomain::Stage(
        const FString StageName
    )
    {
        return MakeShared<Gs2::Freeze::Domain::Model::FStageDomain>(
            Gs2,
            AsShared(),
            StageName == TEXT("") ? TOptional<FString>() : TOptional<FString>(StageName)
        );
    }

    void FGs2FreezeDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2FreezeDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2FreezeDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
    }

    void FGs2FreezeDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

