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
#include "Inbox/Domain/Model/UserAccessToken.h"
#include "Inbox/Model/Gs2InboxEzMessage.h"
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::Inbox::Domain::Iterator
{

	class EZGS2_API FEzDescribeMessagesIterator :
        public TSharedFromThis<FEzDescribeMessagesIterator>
    {
        Gs2::Inbox::Domain::Iterator::FDescribeMessagesIteratorPtr It;
        Gs2::Inbox::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr Connection;
        TOptional<bool> IsRead;

	public:

        explicit FEzDescribeMessagesIterator(
            Gs2::Inbox::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection,
            TOptional<bool> IsRead = TOptional<bool>()
        ) :
            It(
                Domain->Messages(
                    IsRead
                )
            ),
            Domain(Domain),
            GameSession(GameSession),
            Connection(Connection),
            IsRead(IsRead)
        {
        }

		FEzDescribeMessagesIterator(
			const FEzDescribeMessagesIterator& From
		) :
			It(From.It),
			Domain(From.Domain),
			GameSession(From.GameSession),
			Connection(From.Connection),
            IsRead(From.IsRead)
		{
		}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribeMessagesIterator;

			Gs2::Inbox::Domain::Iterator::FDescribeMessagesIterator::FIterator DomainIterator;
			Gs2::UE5::Inbox::Model::FEzMessagePtr CurrentValue;
        	static Gs2::UE5::Inbox::Model::FEzMessagePtr ConvertCurrent(
        		Gs2::Inbox::Domain::Iterator::FDescribeMessagesIterator::FIterator& DomainIterator
        	)
        	{
				return DomainIterator.IsCurrentValid()
	    			? Gs2::UE5::Inbox::Model::FEzMessage::FromModel(DomainIterator.Current())
					: nullptr;
        	}

			explicit FIterator(
				Gs2::Inbox::Domain::Iterator::FDescribeMessagesIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(ConvertCurrent(DomainIterator))
			{}

		public:
			explicit FIterator(
				FEzDescribeMessagesIterator& Iterable
			) :
			    FIterator(Iterable.begin())
			{}

			FIterator(
			    const FIterator& Iterator
            ) :
                DomainIterator(Iterator.DomainIterator),
                CurrentValue(Iterator.CurrentValue)
            {}

			FIterator& operator*()
			{
				return *this;
			}

			const FIterator& operator*() const
			{
				return *this;
			}

			FIterator* operator->()
			{
				return this;
			}

			const FIterator* operator->() const
			{
				return this;
			}

			FIterator& operator++()
			{
				++DomainIterator;
				CurrentValue = ConvertCurrent(DomainIterator);
				return *this;
			}
            Gs2::UE5::Inbox::Model::FEzMessagePtr& Current()
            {
                return CurrentValue;
            }

            Gs2::Core::Model::FGs2ErrorPtr Error()
            {
                return DomainIterator.Error();
            }

            bool IsError() const
            {
                return DomainIterator.IsError();
            }

            void Retry()
            {
                DomainIterator.Retry();
            }

			friend bool operator== (const FIterator& a, const FIterator& b)
			{
				return a.DomainIterator == b.DomainIterator;
			}
			friend bool operator!= (const FIterator& a, const FIterator& b)
			{
				return !operator==(a, b);
			}
		};

		FIterator OneBeforeBegin()
		{
			return FIterator(It->OneBeforeBegin());
		}
		FIterator begin()
		{
			return FIterator(It->begin());
		}
		FIterator end()
		{
			return FIterator(It->end());
		}
    };
	typedef TSharedPtr<FEzDescribeMessagesIterator> FEzDescribeMessagesIteratorPtr;
}
