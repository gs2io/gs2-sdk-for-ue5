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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Freeze/Gs2Freeze.h"

// Model
#include "Freeze/Domain/Model/Stage.h"
#include "Freeze/Domain/Model/Output.h"

// Iterator
#include "Freeze/Domain/Iterator/DescribeStagesIterator.h"
#include "Freeze/Domain/Iterator/DescribeOutputsIterator.h"

// Notification

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Freeze::Domain
{

    class GS2FREEZE_API FGs2FreezeDomain:
        public TSharedFromThis<FGs2FreezeDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Gs2::Freeze::FGs2FreezeRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2FreezeDomain(
            const Core::Domain::FGs2Ptr& Gs2
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2FreezeDomain(
            const FGs2FreezeDomain& From
        );

        Gs2::Freeze::Domain::Iterator::FDescribeStagesIteratorPtr Stages(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStages(
            TFunction<void()> Callback
        );

        void UnsubscribeStages(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Freeze::Domain::Model::FStageDomain> Stage(
            const FString StageName
        );

        void UpdateCacheFromStampSheet(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromStampTask(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result
        );

        void HandleNotification(
            const FString Action,
            const FString Payload
        );

        DECLARE_MULTICAST_DELEGATE_OneParam(FIssueTransactionDelegate, Gs2::Core::Domain::Model::FIssueTransactionEventPtr);
        FIssueTransactionDelegate OnIssueTransaction;
    };
    typedef TSharedPtr<FGs2FreezeDomain> FGs2FreezeDomainPtr;
}
